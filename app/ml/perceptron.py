'''
    read: https://com-cog-book.github.io/com-cog-book/features/perceptron.html
'''
import numpy as np
import pandas as pd 
import altair as alt

def random_weights(X, random_state: int):
    '''
        X : 2d array (matrix), shape = [n_samples, n_features]
        w : array, shape = [w_bias + n_features]
        common practice: start with small weights
    '''
    rand = np.random.RandomState(random_state)
    w = rand.normal(loc=0.0, scale=0.01, size=1 + X.shape[1])
    return w

def net_input(X, w):
    '''
        Linear Aggregation Function
    '''
    return np.dot(X, w[1:]) + w[0]

def predict(X, w):
    '''
        Threshold Decision Function
    '''
    return np.where(net_input(X, w) >= 0.0, 1, -1)

def fit(X, y, eta=0.001, n_iter=100):
    errors = []
    w = random_weights(X, random_state=1)
    for exemplar in range(n_iter):
        error = 0
        for xi, target in zip(X, y):
                delta = eta*(target - predict(xi, w))
                w[1:] += delta * xi
                w[0] += delta
                error += int(delta != 0.0)
        errors.append(error)
    return w, errors

def species_generator(mu1, sigma1, mu2, sigma2, n_samples, target, seed):
    ''' 
        creates [n_samples, 2] array 
        
        Parameters
        ----------
        mu1, sigma1: int, shape = [n_samples, 2]
            mean feature-1, std-dev feature-1
        mu2, sigma2: int, shape = [n_samples, 2]
            mean feature-2, std-dev feature-2
        n_samples: int, shape = [n_samples, 1]
            number of sample cases
        target: int, shape = [1]
            target value
        seed: int
            random seed for reproducibility

        Return
        ------
        X: ndim-array, shape [n_samples, 2]
            matrix of feature vectors
        y: 1d-vector, shape = [n_samples, 1]
            target vector
    '''
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
n_samples = 100
target = 1
seed = 100

# aX: feature matrix (weight, wingspan)
# ay: target value (1)
aX, ay = species_generator(albatross_weight_mean, albatross_weight_variance,
                           albatross_wingspan_mean, albatross_wingspan_variance,
                           n_samples, target, seed)

albatross_dic = {
    'weight-(g)': aX[:,0],
    'wingspan-(cm)':aX[:,1],
    'species': ay,
    'url':"https://raw.githubusercontent.com/pabloinsente/nn-mod-cog/master/notebooks/images/albatross.png"
}

# put values in relational talbe (pandas dataframe)
albatross_df = pd.DataFrame(albatross_dic)

owl_weight_mean = 1000
owl_weight_variance = 200
owl_wingspan_mean = 100
owl_wingspan_variance = 15
n_samples = 100
target = -1
seed = 100

# oX: feature matrix (weight, wingspan)
# oy: target value (-1)
oX, oy = species_generator(owl_weight_mean, owl_weight_variance,
                           owl_wingspan_mean, owl_wingspan_variance,
                           n_samples, target, seed)

owl_dic = {
    'weight-(g)': oX[:,0],
    'wingspan-(cm)': oX[:,1],
    'species': oy,
    'url': "https://raw.githubusercontent.com/pabloinsente/nn-mod-cog/master/notebooks/images/owl.png"
}

# put values in a relational table (pandas dataframe)
owl_df = pd.DataFrame(owl_dic)

#df = albatross_df.append(owl_df, ignore_index=True)
#df = albatross_df.concat(owl_df, ignore_index=True)
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

w, errors = fit(X, y, eta=0.01, n_iter=200)

y_pred = predict(X, w)
num_correct_predictions = (y_pred == y).sum()
accuracy = (num_correct_predictions / y.shape[0]) * 100
print('Perceptron accuracy: %.2f%%' % accuracy)

error_df = pd.DataFrame({'error': errors, 'time-step': np.arange(0, len(errors))})
chart = alt.Chart(error_df).mark_line().encode(x="time-step", y="error").properties(title='Chart 2')

chart.save('chart.html')


