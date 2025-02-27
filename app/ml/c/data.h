#define N_SAMPLES 200

int n_features = 2;

double dataset[][200] = {
{8533.123959741868,1272.3112250290662,7010.278771821784,9464.45866863542,9190.275697538897,1237.9244536058252,8798.49668862943,8739.009552638157,8560.20304517161,1116.114667158855,8564.448670662028,9176.94373537712,7954.406128735345,9922.428642050916,1230.6071605127288,1406.9215123009867,1249.8939485453957,9823.786148106678,8326.051409398962,823.6403221033966,9177.919686844243,9653.477657348623,1073.8327914214012,866.3656526373145,9653.16320881543,661.8766347232792,762.3964805364561,9204.001155418706,1087.0326976245785,10039.798459804248,9600.355809227343,949.6241721573574,1036.9037381127885,8649.491501836466,8916.471085287498,7647.506538893116,1044.23593384428,8213.351920696296,9749.665760887161,1366.3872163651072,8164.632097832547,7691.576480495342,984.7953068550753,1187.4164402217905,1011.1352029709553,9087.097591918331,9087.090774266944,9821.537151519833,7854.247511152858,7914.88076091095,8939.181227420302,8635.242458025597,1205.384287879958,502.5696929554461,1294.142773322426,10501.258741569733,791.1580244581367,1150.0889523068356,9010.83883890289,779.0953814675413,9274.144322662001,883.280989935467,1137.3780132276809,9588.96417065906,7635.238395409464,9600.362664261473,711.3566009549327,9623.057919458453,10627.686049203947,889.8571176170815,848.729538881113,1122.6077763375092,9406.247672393856,908.3946028994751,10089.244900116264,8049.585922145825,9411.375073115505,8116.381525870165,9147.614952451155,9999.575794181583,8014.052388868059,8574.975698518472,1068.5360806655003,1138.0242940449416,908.8106145063996,822.0537037469933,7600.187621556242,1150.0906660653682,9538.17664456773,1146.2000687669617,9022.62690785846,9295.331165685604,1134.5441611419321,1021.7726935667359,1308.3210349026813,8394.918155524452,8798.051170782888,834.4135271268258,9044.540811883822,9342.586296477393,8848.40333534146,8465.462610549257,8734.578291957752,1047.5689243847244,1021.7743979795829,949.512792695722,1005.6567269646147,1001.4629126457806,1163.290802203857,890.050761292902,672.8941201238356,9490.431105350037,713.5618777882146,8337.654108507304,8633.5784115979,8509.64901161747,9002.413947224972,9014.911159590449,10465.548865460429,1003.7277898976121,8536.93934016721,753.5130972170148,686.6624940843218,9951.6978144233,653.3808752693437,1163.3694143371558,1323.796332135052,8143.965335545366,650.0469053890605,1073.2186452334608,9348.130790498313,7845.426403819731,9549.512052910724,1002.7097097257225,877.4122529043675,1102.8437682788765,893.743924629618,8105.345402995651,933.6445729894383,1071.501550633473,884.2348350418023,738.6015321838362,10233.284139610725,8288.214814987972,7613.523501077375,1259.949614951062,1044.479921711061,631.7623399626566,9286.006202533892,1375.3146853924331,984.0777508165202,1205.9465370266691,8559.428470468325,1180.9948242933363,1101.561918098464,8310.218122791615,7709.13719774226,8448.625617528198,811.9907676910464,1051.0002888546762,8040.439040644855,803.337980174074,1196.2641573902463,9723.979297173344,9292.874580933843,1085.646574119348,1000.7915187975199,658.809598852366,831.5128523497405,9552.097176179766,760.1097601612138,9584.800275067846,785.9913338863414,8698.47731986482,1147.2410426647648,10176.571093289704,924.619329966205,9005.851650583123,9785.056629560986,979.1177713218744,8936.31100326608,7527.049359850626,962.9971778205772,862.1564043820493,912.3728754591166,827.554530697904,728.7201902277375,10295.185328540207,677.2842994355649,8247.963070764185,934.7523881595395,9003.16607519008,776.3363507489128,1155.7644798646133,962.1008338353649,891.1121676655072,8294.561288413586,8851.988711282309,7746.649976337287,1000.6034868062428},
{291.5256980011316,99.70903621056303,331.5233344863841,291.683673283187,315.06124375383956,77.3862225960342,272.0600131009343,317.8919541152003,296.69580894718536,93.76275496239025,271.6991415829495,302.64855602297547,299.6730919448503,240.5336905189823,55.400267889236716,98.10698224429635,89.16773844916369,313.8678131703318,278.05656030720354,99.86652005061835,270.0455923783366,276.2803287014165,107.69611568259468,90.38860115484142,319.0455125216378,101.6182619620992,134.47980911070513,284.95171644549924,101.4270916534818,341.49586335893133,275.6549173871797,79.04500982570075,96.41930696027981,260.83837531584265,274.5795391830668,302.15768261613226,101.9864170172316,287.6674125663361,271.41866203103416,93.1611697117897,271.0512777536083,338.8652452686799,97.37827668322753,78.56399652327563,111.39539679775308,285.91163600529956,293.6033790576382,259.69622565754946,298.40918826131775,314.941113101983,296.50436891097,296.85469665249724,69.7721692431621,123.64250086478809,94.77311604021445,323.4105396589629,78.28845831520623,81.74118804038477,267.8112220765409,79.622455948603,277.27477986345275,93.6442735008487,96.75909819995108,318.9872172932197,335.51987171013536,310.459956090415,82.09171034812093,324.7381577038045,297.4759763257285,129.85410474631135,119.44393879598586,101.95372683029053,277.04516800246824,80.55412289274774,299.6120482807507,345.9730788142735,290.996471299767,272.829941264804,295.2257426137064,285.5569845988849,308.5935287172522,331.7234187684647,82.95608489758956,92.28355162946822,97.64102248937293,96.55723370140066,265.90697588478076,107.84496706781127,292.6907601464675,114.23507164757889,288.17249757829654,310.2614875767929,94.5180701098506,95.20253429322868,130.70070952723208,325.92525172798116,300.6663455627773,104.04980857946633,315.1938623970041,295.39430643145784,306.34735951882135,287.18480153978857,304.447816188909,111.29593281537969,89.43372700397465,100.49975917208295,91.12937318372242,111.69439455495544,114.28413439122836,97.52185671038902,129.14893395150995,302.60496910705405,98.80689119598833,305.3997447726218,274.072163856997,291.23758167302316,312.98345854509364,289.1360398318566,290.8815596157196,91.85202987389242,314.73990338036424,106.44514653793914,106.33570330632968,269.84829679471227,94.85053476726296,82.2102465260624,76.8907596317108,300.44427856078784,74.43023191358557,74.7265005747223,301.90278887130904,276.12228046416124,295.6787975999348,75.85841655740569,93.42818625476735,93.24735347482523,123.79256407634853,297.3039737602001,103.33586214168173,111.44775469089988,111.05492753527318,99.7548189586377,340.93427936964275,295.4096449352009,293.1340463563506,131.12189751919848,77.53419428375246,104.51574195682099,315.2636729211998,117.55790474422216,116.40529974488082,110.40085987774883,339.8054729950818,83.58935603451647,82.78387600185121,334.0724797624141,303.85834383646613,286.3015652950554,106.99449052535785,88.71378733412445,308.7173450502982,90.75055942475208,96.26666999412838,278.1191413793553,266.3020007662964,96.54572982359338,115.25896514876754,126.6399037826015,83.54242023040266,289.7114021726243,106.53800878772365,318.9800955301052,100.33320892059086,341.5542446450041,114.2404129699148,293.0308213869526,131.16568348375304,315.5925260732739,295.02222665883784,80.93465438730009,321.87373299317443,306.0209892757613,91.000254327267,89.72617397129154,70.628781486882,125.55435982181058,111.2058348264872,269.1876795089477,102.8937578773496,309.3259873671438,113.4189655864002,320.3452868650234,97.97798032015008,118.55361827785339,104.76051963911601,78.7743561872121,299.8220267341578,288.00033910302267,308.4476044084396,109.73759390882023}
};

int species[] = {
1,
-1,
1,
1,
1,
-1,
1,
1,
1,
-1,
1,
1,
1,
1,
-1,
-1,
-1,
1,
1,
-1,
1,
1,
-1,
-1,
1,
-1,
-1,
1,
-1,
1,
1,
-1,
-1,
1,
1,
1,
-1,
1,
1,
-1,
1,
1,
-1,
-1,
-1,
1,
1,
1,
1,
1,
1,
1,
-1,
-1,
-1,
1,
-1,
-1,
1,
-1,
1,
-1,
-1,
1,
1,
1,
-1,
1,
1,
-1,
-1,
-1,
1,
-1,
1,
1,
1,
1,
1,
1,
1,
1,
-1,
-1,
-1,
-1,
1,
-1,
1,
-1,
1,
1,
-1,
-1,
-1,
1,
1,
-1,
1,
1,
1,
1,
1,
-1,
-1,
-1,
-1,
-1,
-1,
-1,
-1,
1,
-1,
1,
1,
1,
1,
1,
1,
-1,
1,
-1,
-1,
1,
-1,
-1,
-1,
1,
-1,
-1,
1,
1,
1,
-1,
-1,
-1,
-1,
1,
-1,
-1,
-1,
-1,
1,
1,
1,
-1,
-1,
-1,
1,
-1,
-1,
-1,
1,
-1,
-1,
1,
1,
1,
-1,
-1,
1,
-1,
-1,
1,
1,
-1,
-1,
-1,
-1,
1,
-1,
1,
-1,
1,
-1,
1,
-1,
1,
1,
-1,
1,
1,
-1,
-1,
-1,
-1,
-1,
1,
-1,
1,
-1,
1,
-1,
-1,
-1,
-1,
1,
1,
1,
-1
};
