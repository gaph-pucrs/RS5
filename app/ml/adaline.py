import numpy as np
import pandas as pd
import altair as alt

def random_weights(X, random_state: int):
    ''' 
        X: 2d array, X.shape = [n_samples, n_features] 
        w: array, shape = [w_bias + n_features]
    '''
    rand = np.random.RandomState(random_state)
    w = rand.normal(loc=0.0, scale=0.01, size=1+X.shape[1])
    return w

def net_input(X, w):
    return np.dot(X, w[1:]) + w[0]

def predict(X, w):
    return np.where(net_input(X, w)>=0, 1, -1)

def fit(X, y, eta=0.001, n_iter=1):
    mse_iteration = []
    w = random_weights(X, random_state=1)
    for pair in range(n_iter):
        output = net_input(X, w)
        print('Iteration: %d\n' % pair)
        print(output)
        gradient = 2*(output - y)
        print('Priting grad...\n')
        print(gradient)
        w[1:] += eta*(X.T @-gradient)
        w[0] += eta*-gradient.sum()
        mse = (((y - output)**2).sum())/len(y)
        mse_iteration.append(mse)
    return w, mse_iteration

def species_generator(mu1, sigma1, mu2, sigma2, n_samples, target, seed):
    rand = np.random.RandomState(seed)
    f1 = rand.normal(mu1, sigma1, n_samples)
    f2 = rand.normal(mu2, sigma2, n_samples)
    X = np.array([f1, f2])
    X = X.transpose()
    y = np.full((n_samples), target)
    return X, y

albatross_weight_mean = 9000
albatross_weight_variance = 800
albatross_wingspan_mean = 300
albatross_wingspan_variance = 20
n_samples = 20 
target = 1
seed = 100

aX, ay = species_generator(albatross_weight_mean, albatross_weight_variance,
                           albatross_wingspan_mean, albatross_wingspan_variance,
                           n_samples, target, seed)

albatross_dic = {
    'weight-(g)': aX[:,0],
    'wingspan-(cm)': aX[:,1],
    'species': ay,
    'url': "https://raw.githubusercontent.com/pabloinsente/nn-mod-cog/master/notebooks/images/albatross.png"
}

albatross_df = pd.DataFrame(albatross_dic)

owl_weight_mean = 1000 
owl_weight_variance =  200 
owl_wingspan_mean = 100 
owl_wingspan_variance = 15 
# n_samples = 20 
target = -1
seed = 100

oX, oy = species_generator(owl_weight_mean, owl_weight_variance,
                           owl_wingspan_mean, owl_wingspan_variance,
                           n_samples,target,seed )

owl_dic = {
    'weight-(g)': oX[:,0],
    'wingspan-(cm)': oX[:,1],
    'species': oy,
    'url': "https://raw.githubusercontent.com/pabloinsente/nn-mod-cog/master/notebooks/images/owl.png"
}

owl_df = pd.DataFrame(owl_dic)

df = pd.concat([albatross_df, owl_df], ignore_index=True)

alt.Chart(df).mark_image(
    width=20,
    height=20
).encode(
    x="weight-(g)",
    y="wingspan-(cm)",
    url="url"
).properties(
    title='Chart 1'
)

df_shuffle = df.sample(frac=1, random_state=1).reset_index(drop=True)
X = df_shuffle[['weight-(g)', 'wingspan-(cm)']].to_numpy()
y = df_shuffle['species'].to_numpy()

w, mse = fit(X, y, eta=1e-10, n_iter=12)

y_pred = predict(X, w)
num_correct_predictions = (y_pred == y).sum()
accuracy = (num_correct_predictions/y.shape[0])*100
print('ADALINE accuracy: %.2f%%' % accuracy)

mse_df = pd.DataFrame({'mse': mse, 'time-step': np.arange(0, len(mse))})
# base = alt.Chart(mse_df).encode(x="time-step:0")
chart_2 = alt.Chart(mse_df).mark_line().encode(x="time-step", y="mse").properties(width=400, title='Chart 2')
chart_2.save('chart_2.html')
