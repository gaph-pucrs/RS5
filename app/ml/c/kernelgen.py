import numpy as np

def random_weights(X, random_state: int):
    rand = np.random.RandomState(random_state)
    w = rand.normal(loc=0.0, scale=0.01, size=1+X)
    return w

w = random_weights(100, random_state=1)
w_array = np.array(w)
w_c_array = "{\n" + ",\n".join(map(str, w_array)) + "\n}"

file_path = 'weights.h'
with open(file_path, 'w') as file:
    file.write(f"double weights[] = {w_c_array};\n")

print(f"(+) Weights generated in {file_path} file\n")
