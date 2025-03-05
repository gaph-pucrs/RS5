import numpy as np
from keras.models import Sequential
from keras.layers.core import Dense

# expected values
y = np.array([[0, 1, 1, 0]]).T

# features
X = np.array([[0, 0, 1, 1],
              [0, 1, 0, 1]]).T

model = Sequential()
model.add(Dense(16, input_dim=2, activation='sigmoid'))
model.add(Dense(1, activation='sigmoid'))

model.compile(loss='mean_squared_error',
              optimizer='adam',
              metrics=['binary_accuracy', 'mean_squared_error'])

history = model.fit(X, y, epochs=3000, verbose=0)

errors = history.history['loss']
df2 = pd.DataFrame({"errors": errors, "time-step": np.arange(0, len(errors))})
alt.Chart(df2).mark_line().encode(x="time-step", y="errors").properties(title='Chart 3')

y_pred = model.predict(X).round()
num_correct_predictions = (y_pred == y).sum()
accuracy = (num_correct_predictions/y.shape[0])*100
print('KERAS: Multi-layer perceptron accuracy: %.2f%%' % accuracy)
