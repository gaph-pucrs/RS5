import numpy as np
import random

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
n_samples = 100
target = 1
seed = 100

aX, ay = species_generator(albatross_weight_mean, albatross_weight_variance,
                           albatross_wingspan_mean, albatross_wingspan_variance,
                           n_samples, target, seed)

owl_weight_mean = 1000
owl_weight_variance = 200
owl_wingspan_mean = 100
owl_wingspan_variance = 15
n_samples = 100
target = -1
seed = 100

oX, oy = species_generator(owl_weight_mean, owl_weight_variance,
                           owl_wingspan_mean, owl_wingspan_variance,
                           n_samples, target, seed)

albatross_dict = [{
    'weight-(g)': aX[i,0],
    'wingspan-(cm)': aX[i,1],
    'species': ay[i]
} for i in range (len(aX))]

owl_dict = [{
    'weight-(g)': oX[i,0],
    'wingspan-(cm)': oX[i,1],
    'species': oy[i]
} for i in range (len(oX))]

combined_dict = albatross_dict + owl_dict
random.shuffle(combined_dict)

weights = [entry['weight-(g)'] for entry in combined_dict]
weights_array = np.array(weights)
#weights_c_array = "{\n" + ",\n".join(map(str, weights_array)) + "\n}"

wingspans = [entry['wingspan-(cm)'] for entry in combined_dict]
wingspans_array = np.array(wingspans)
#wingspans_c_array = "{\n" + ",\n".join(map(str, wingspans_array)) + "\n}"

species = [entry['species'] for entry in combined_dict]
species_array = np.array(species)
species_c_array = "{\n" + ",\n".join(map(str, species_array)) + "\n}" 

dataset = np.column_stack((weights_array, wingspans_array))
#dataset_c_array = "{\n" + ",\n".join([f"{{ {weight}, {wingspan} }}" for weight, wingspan in dataset]) + "\n}"

dataset_c_array = "{\n{" + ",".join(map(str, weights_array)) + "}," + "\n{" + ",".join(map(str, wingspans_array)) + "}\n}"


file_path = 'data.h'
with open(file_path, 'w') as file:
    #file.write(f"int weights = {weights_c_array};\n")
    #file.write(f"int wingspans = {wingspans_c_array};\n")
    file.write(f"#define N_SAMPLES {2*n_samples}\n\n")
    #file.write(f"int n_samples = {n_samples};\n\n")
    file.write(f"int n_features = 2;\n\n")
    file.write(f"double dataset[][{2*n_samples}] = {dataset_c_array};\n\n")
    file.write(f"int species[] = {species_c_array};\n")

print(f"(+) Data generated into {file_path} file\n")
