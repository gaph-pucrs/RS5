import torch
import torch.nn as nn
import torch.nn.functional as F
from collections import OrderedDict
import math

class MMConv(nn.Module):
    def __init__(self, num_input_features, growth_rate, bottleneck_width):
        super(MMConv, self).__init__()
        inter_channel = int(growth_rate  * bottleneck_width/2)
        growth_branch = int(growth_rate / 4)
        self.branch11 = ConvNormRelu(num_input_features, inter_channel, kernel_size=1)
        self.branch33a = ConvNormRelu(inter_channel, inter_channel, kernel_size=3,padding=1)
        self.branch33b = ConvNormRelu(inter_channel, growth_branch, kernel_size=3,padding=1)
        self.branch33c = ConvNormRelu(growth_branch, growth_branch, kernel_size=3,padding=1)

    def forward(self, x):
        y0 = self.branch11(x)
        y1 = self.branch33a(y0)
        y2 = self.branch33b(y1)
        y3 = self.branch33c(y2)
        z=torch.cat([x, y1, y2,y3], 1)
        return z


class MMBlock(nn.Sequential):
    def __init__(self, num_layers, num_input_features, bn_size, growth_rate):
        super(MMBlock, self).__init__()
        for i in range(num_layers):
            layer = MMConv(num_input_features + i * growth_rate, growth_rate, bn_size)
            self.add_module('mmLayer%d' % (i + 1), layer)

class StemBlock(nn.Module):
    def __init__(self, num_input_channels, num_init_features):
        super(StemBlock, self).__init__()

        self.stemConv = nn.Sequential(
            nn.Conv2d(in_channels=num_input_channels, out_channels=num_init_features, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(num_init_features),
            nn.ReLU()
        )
                
    def forward(self, x):
        out2 = self.stemConv(x)
        return out2

class ConvNormRelu(nn.Module):

    def __init__(self, in_channels, out_channels, **kwargs):
        super(ConvNormRelu, self).__init__()
        self.conv = nn.Conv2d(in_channels, out_channels, bias=False, **kwargs)
        self.norm = nn.BatchNorm2d(out_channels) 

    def forward(self, x):
        x = self.conv(x)
        x = self.norm(x)
        x = F.relu(x, inplace=True)
        return x

class LMFRNet(nn.Module):
    def __init__(self, growth_rate=[24, 24, 24, 24], block_config=[3, 4, 8, 3],
                 num_init_features=32, bottleneck_width=[1, 1, 1, 1],  num_classes=10):
        
        super(LMFRNet, self).__init__()


        self.features = nn.Sequential(OrderedDict([
            ('stemBlock', StemBlock(3, num_init_features)), 
        ]))
        growth_rates = growth_rate
        bottleneck_widths = bottleneck_width

        num_features = num_init_features
        for i, num_layers in enumerate(block_config):
            block = MMBlock(num_layers=num_layers, num_input_features=num_features,
                                bn_size=bottleneck_widths[i], growth_rate=growth_rates[i])
            self.features.add_module('MMCBlock%d' % (i + 1), block)
            num_features = num_features + num_layers * growth_rates[i]

            self.features.add_module('tran_ConvNormRelu%d' % (i + 1), ConvNormRelu(
                num_features, num_features, kernel_size=1, stride=1, padding=0))

            if i != len(block_config) - 1:
                self.features.add_module('tran_pool%d' % (i + 1), nn.AvgPool2d(kernel_size=2, stride=2))
                num_features = num_features
                
        self.classifier = nn.Linear(num_features, num_classes)
        self.add_module('fc', self.classifier)
        self._initialize_weights()

    def forward(self, x):
        features = self.features(x)
        out = F.avg_pool2d(features, kernel_size=(features.size(2), features.size(3))).view(features.size(0), -1)
        out = self.classifier(out)
        return out

    def _initialize_weights(self):
        for m in self.modules():
            if isinstance(m, nn.Conv2d):
                n = m.kernel_size[0] * m.kernel_size[1] * m.out_channels
                m.weight.data.normal_(0, math.sqrt(2. / n))
                if m.bias is not None:
                    m.bias.data.zero_()
            elif isinstance(m, nn.BatchNorm2d):
                m.weight.data.fill_(1)
                m.bias.data.zero_()
            elif isinstance(m, nn.Linear):
                n = m.weight.size(1)
                m.weight.data.normal_(0, 0.01)
                m.bias.data.zero_()


if __name__ == '__main__':
    model = LMFRNet()

    from thop import profile
    input_shape = (1, 3, 32, 32)
    flops, params = profile(model, inputs=(torch.randn(*input_shape),))
    print(f"Model flops: {flops}")
    print(f"Model Params: {params}")

    def print_size(self, input, output):
        print(torch.typename(self).split('.')[-1], ' output size:',output.data.size())

    for layer in model.features:
        layer.register_forward_hook(print_size)
