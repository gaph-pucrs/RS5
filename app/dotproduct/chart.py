import matplotlib.pyplot as plt

# Data
X = [8, 16, 32, 64, 128, 256, 512, 1024]
Scalar_32b = [104, 177, 323, 615, 1199, 2367, 4703, 9375]
Scalar_16b = [153, 252, 450, 846, 1638, 3222, 6390, 12726]
Scalar_8b = [138, 229, 411, 775, 1503, 2959, 5871, 11695]

Vector_32b_m1 = [92, 166, 314, 610, 1202, 2386, 4754, 9490]
Vector_16b_m1 = [55, 90, 160, 300, 580, 1140, 2260, 4500]
Vector_8b_m1 = [55, 55, 89, 157, 293, 565, 1109, 2197]

Vector_32b_m2 = [68, 118, 218, 418, 818, 1618, 3218, 6418]
Vector_16b_m2 = [59, 66, 112, 204, 388, 756, 1492, 2964]
Vector_8b_m2 = [57, 59, 66, 111, 201, 381, 741, 1461]

Vector_32b_m4 = [74, 95, 172, 326, 634, 1250, 2482, 4946]
Vector_16b_m4 = [63, 72, 89, 158, 296, 572, 1124, 2228]
Vector_8b_m4 = [61, 63, 72, 89, 157, 293, 565, 1109]

Vector_32b_m8 = [82, 104, 146, 275, 533, 1049, 2081, 4145]
Vector_16b_m8 = [71, 80, 98, 132, 245, 471, 923, 1827]
Vector_8b_m8 = [69, 71, 80, 98, 132, 244, 468, 916]

# Plotting
fig, axs = plt.subplots(3, 1, figsize=(12, 15), sharex=True)

dimensions = ['32b', '16b', '8b']
scalar_data = [Scalar_32b, Scalar_16b, Scalar_8b]
vector_data = [
    [Vector_32b_m1, Vector_32b_m2, Vector_32b_m4, Vector_32b_m8],
    [Vector_16b_m1, Vector_16b_m2, Vector_16b_m4, Vector_16b_m8],
    [Vector_8b_m1, Vector_8b_m2, Vector_8b_m4, Vector_8b_m8]
]
markers = ['o', 's', 'D', '^']
labels = ['m1', 'm2', 'm4', 'm8']

for i, (dim, scalar, vectors) in enumerate(zip(dimensions, scalar_data, vector_data)):
    # Use index positions for equally distributed X-axis
    axs[i].plot(range(len(X)), scalar, label=f'Scalar_{dim}', marker='x', color='black', linewidth=2)
    for j, vec in enumerate(vectors):
        axs[i].plot(range(len(X)), vec, label=f'Vector_{dim}_{labels[j]}', marker=markers[j])

    axs[i].set_title(f'{dim} Performance')
    axs[i].set_ylabel('Values')
    axs[i].set_yscale('log')  # Set Y-axis to logarithmic scale
    axs[i].legend()
    axs[i].grid(True)

    # Set the X-axis tick positions and labels for each subplot
    axs[i].set_xticks(range(len(X)))
    axs[i].set_xticklabels(X)

# Common X-axis label
plt.xlabel('Amount of Cycles (X)')
plt.suptitle('Performance Comparison (Logarithmic Scale)', fontsize=16)
plt.tight_layout(rect=[0, 0, 1, 0.96])

# Show the plot
plt.show()
