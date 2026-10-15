import matplotlib.pyplot as plt
import pandas as pd
import os

current_file_dir = os.path.dirname(os.path.abspath(__file__))

results_dir = os.path.join(current_file_dir, "results")
benchmarks_list = [entry for entry in os.listdir(results_dir) if os.path.isdir(os.path.join(results_dir, entry)) and entry != "charts" and 'dotproduct' in entry]

print("*********************************")
print(f'!!! Generating Charts !!!')
print("*********************************\n")

for benchmark in benchmarks_list:
    df = pd.read_csv(os.path.join(results_dir, benchmark, f'{benchmark}.csv'))

    scalar_cycles = df.at[0, "CYCLES"]
    df = df.drop(0).reset_index(drop=True)

    vlen_values = sorted(df['VLEN'].unique())
    configurations = df[['BUS_WIDTH', 'LANES']].drop_duplicates().sort_values(['BUS_WIDTH', 'LANES'])

    colors = {0: 'tab:gray', 1: 'tab:blue', 2: 'tab:olive', 4: 'tab:orange', 8: 'tab:green'}
    patterns = {32: '', 64: '//'}
    bar_width = 0.6
    bar_spacing = 0.1

    # Prepare data structure: for each VLEN, get cycles for each configuration
    vlen_data = {}
    for vlen in vlen_values:
        vlen_data[vlen] = []
        for _, config in configurations.iterrows():
            bus_width, lanes = config.BUS_WIDTH, config.LANES
            cycles = df[(df['VLEN'] == vlen) & (df['BUS_WIDTH'] == bus_width) & (df['LANES'] == lanes)]['CYCLES']
            vlen_data[vlen].append(cycles.values[0] if len(cycles) > 0 else 0)

    # Set up the plot with dual y-axes
    fig, ax = plt.subplots(figsize=(14, 8))
    ax2 = ax.twinx()  # Create second y-axis

    # Reorganize data to show all bars together for each VLEN
    all_bars_data = []
    all_labels = []
    all_colors = []
    all_hatches = []
    x_positions = []
    vlen_tick_positions = []

    # Start with scalar bar at x=0
    scalar_x = 0
    scalar_bar = ax.bar(scalar_x, scalar_cycles, bar_width, color=colors[0], label='Scalar')

    # Add scalar to tick positions
    vlen_tick_positions.append(scalar_x)
    vlen_labels = ['Scalar']

    current_x = 2  # Start vector bars with some gap after scalar

    for vlen_idx, vlen in enumerate(vlen_values):
        vlen_bars = []
        vlen_start_x = current_x

        # Add all bars for this VLEN
        for config_idx, (_, config) in enumerate(configurations.iterrows()):
            bus_width, lanes = config.BUS_WIDTH, config.LANES
            cycles = vlen_data[vlen][config_idx]

            if cycles > 0:  # Only add bars with data
                all_bars_data.append(cycles)
                all_labels.append(f'Bus Width: {bus_width}, Lanes: {lanes}')
                all_colors.append(colors[lanes])
                all_hatches.append(patterns[bus_width])
                x_positions.append(current_x)
                current_x += bar_width + bar_spacing

        # Calculate center position for VLEN label
        vlen_end_x = current_x - bar_width
        vlen_center = (vlen_start_x + vlen_end_x) / 2
        vlen_tick_positions.append(vlen_center)
        vlen_labels.append(str(vlen))

        # Add gap between VLEN groups
        current_x += bar_width * 1.2

    # Create the vector bars on main axis
    bars_list = []
    for i in range(len(all_bars_data)):
        bar = ax2.bar(x_positions[i], all_bars_data[i], bar_width,
                    color=all_colors[i], hatch=all_hatches[i])
        bars_list.extend(bar)

    # Create legend handles for both axes
    legend_handles = []
    legend_labels = []

    # Add scalar (from primary axis)
    legend_handles.append(plt.Rectangle((0,0),1,1, color=colors[0]))
    legend_labels.append('Scalar')

    # Add vector configurations (from secondary axis)
    for i, (_, config) in enumerate(configurations.iterrows()):
        bus_width, lanes = config.BUS_WIDTH, config.LANES
        has_data = any(vlen_data[vlen][i] > 0 for vlen in vlen_values)
        if has_data:
            legend_handles.append(plt.Rectangle((0,0),1,1, facecolor=colors[lanes],
                                            hatch=patterns[bus_width]*3))
            legend_labels.append(f'Bus Width: {bus_width}, Lanes: {lanes}')

    # Create the combined legend
    ax.legend(legend_handles, legend_labels, loc='upper right', fontsize=10)

    # Customize the plot
    ax.set_xlabel('VLEN', fontsize=14, fontweight='bold')
    ax.set_ylabel('Scalar Cycles', fontsize=14, fontweight='bold')
    ax2.set_ylabel('Vector Cycles', fontsize=14, fontweight='bold')
    ax.set_title('Performance Analysis: Cycles vs Vector Length (VLEN)', fontsize=16, fontweight='bold', pad=20)

    # Set x-axis
    ax.set_xticks(vlen_tick_positions)
    ax.set_xticklabels(vlen_labels, fontsize=12)

    # Add grid only for main axis
    ax2.grid(True, axis='y')
    ax2.set_axisbelow(True)

    # Set y-axis limits
    vector_max = max(all_bars_data) if all_bars_data else 0
    ax.set_ylim(0, scalar_cycles * 1.05)
    ax2.set_ylim(0, vector_max * 1.15)

    # Color the y-axis labels to match their respective scales
    ax.tick_params(axis='y', labelcolor='red')
    ax2.tick_params(axis='y', labelcolor='black')

    # Add value labels on bars
    # Scalar bar label
    ax.annotate(f'{int(scalar_cycles)}',
            xy=(scalar_x + bar_width/2, scalar_cycles),
            xytext=(0, 3),
            textcoords="offset points",
            ha='center', va='bottom',
            fontsize=10, fontweight='bold', color='#FF6B6B')

    # Vector bars labels
    for bar in bars_list:
        height = bar.get_height()
        if height > 0:  # Only add label if bar has height
            ax2.annotate(f'{int(height)}',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom',
                    fontsize=9, rotation=45)

    # Improve layout
    plt.tight_layout()

    # Show the plot
    plt.show()
    plt.savefig(os.path.join(results_dir, 'charts', f'{benchmark}.png'))

    print(f"✅ Succesful Chart Generation for {benchmark}!!!\n")
