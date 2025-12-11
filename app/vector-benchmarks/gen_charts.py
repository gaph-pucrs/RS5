import matplotlib.pyplot as plt
import pandas as pd
import os
from matplotlib.patches import Rectangle

current_file_dir = os.path.dirname(os.path.abspath(__file__))

results_dir = os.path.join(current_file_dir, "results", "charts")
benchmarks_list = [os.path.splitext(entry)[0] for entry in os.listdir(results_dir) if os.path.isfile(os.path.join(results_dir, entry)) and entry.endswith(".csv")]

print("*********************************")
print(f'!!! Generating Charts !!!')
print("*********************************\n")

def add_broken_axis_markers(ax, break_start, break_end):
    """Add diagonal lines to indicate broken axis"""
    d = .015  # size of diagonal lines
    kwargs = dict(transform=ax.transAxes, color='k', clip_on=False, linewidth=1.5)

    # Get the y-coordinate in axes coordinates for the break
    ylim = ax.get_ylim()
    break_start_norm = (break_start - ylim[0]) / (ylim[1] - ylim[0])
    break_end_norm = (break_end - ylim[0]) / (ylim[1] - ylim[0])

    # Draw break lines at the break boundaries
    ax.plot((-d, +d), (break_start_norm-d, break_start_norm+d), **kwargs)
    ax.plot((-d, +d), (break_end_norm-d, break_end_norm+d), **kwargs)
    ax.plot((1-d, 1+d), (break_start_norm-d, break_start_norm+d), **kwargs)
    ax.plot((1-d, 1+d), (break_end_norm-d, break_end_norm+d), **kwargs)

for benchmark in benchmarks_list:
    df = pd.read_csv(os.path.join(results_dir, f'{benchmark}.csv'))

    scalar_cycles = df.at[0, "CYCLES"]
    df = df.drop(0).reset_index(drop=True)

    vlen_values = sorted(df['VLEN'].unique())
    configurations = df[['BUS_WIDTH', 'LANES']].drop_duplicates().sort_values(['LANES', 'BUS_WIDTH'])

    colors = {0: 'tab:gray', 1: 'tab:blue', 2: 'tab:olive', 4: 'tab:orange', 8: 'tab:green'}
    patterns = {32: '', 64: '//', 128: 'XX', 256: '..'}
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

    # Calculate maximum vector value
    vector_max = 0
    all_bars_data = []
    for vlen in vlen_values:
        for cycles in vlen_data[vlen]:
            if cycles > 0:
                all_bars_data.append(cycles)
                vector_max = max(vector_max, cycles)

    # Check if we need a broken axis (scalar > 120% of max vector)
    use_broken_axis = scalar_cycles > vector_max * 1.2

    if use_broken_axis:
        #print(f"Using broken axis for {benchmark}: Scalar={scalar_cycles}, Max Vector={vector_max}")

        # Create subplots with shared x-axis for broken axis
        fig, (ax_top, ax_bottom) = plt.subplots(2, 1, figsize=(14, 10), sharex=True,
                                               gridspec_kw={'height_ratios': [1, 3], 'hspace': 0.05})

        # Define break points
        break_start = vector_max * 1.1
        break_end = scalar_cycles * 0.9

        # Set y-limits for broken axis
        ax_top.set_ylim(break_end, scalar_cycles * 1.05)
        ax_bottom.set_ylim(0, break_start)

        # Hide spines between the two axes
        ax_top.spines['bottom'].set_visible(False)
        ax_bottom.spines['top'].set_visible(False)
        ax_top.xaxis.tick_top()
        ax_top.tick_params(labeltop=False)
        ax_bottom.xaxis.tick_bottom()
        ax_bottom.tick_params(axis='y', labelsize=14)
        ax_top.tick_params(axis='y', labelsize=14)

        # Add broken axis markers
        add_broken_axis_markers(ax_top, break_end, scalar_cycles * 1.05)
        add_broken_axis_markers(ax_bottom, 0, break_start)

        main_ax = ax_bottom  # Use bottom axis for vector data
        scalar_ax = ax_top   # Use top axis for scalar data

    else:
        # Use standard single axis
        fig, ax = plt.subplots(figsize=(14, 8))
        main_ax = ax
        scalar_ax = ax
        main_ax.tick_params(axis='y', labelsize=14)

    # Prepare x-positions and labels
    all_labels = []
    all_colors = []
    all_hatches = []
    x_positions = []
    vlen_tick_positions = []

    # Start with scalar bar at x=0
    scalar_x = 0

    if use_broken_axis:
        # Draw scalar bar on both axes to show complete bar
        # Bottom part of the bar (from 0 to break_start)
        scalar_bar_bottom = ax_bottom.bar(scalar_x, break_start, bar_width, color=colors[0], label='Scalar')
        # Top part of the bar (from break_end to scalar_cycles)
        scalar_bar_top = ax_top.bar(scalar_x, scalar_cycles - break_end, bar_width,
                                   bottom=break_end, color=colors[0])
        scalar_bar = scalar_bar_bottom  # For legend purposes
    else:
        scalar_bar = scalar_ax.bar(scalar_x, scalar_cycles, bar_width, color=colors[0], label='Scalar')

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
        bar = main_ax.bar(x_positions[i], all_bars_data[i], bar_width,
                    color=all_colors[i], hatch=all_hatches[i])
        bars_list.extend(bar)

    # CREATE THREE SEPARATE LEGENDS SIDE BY SIDE
    
    # Column 1: Scalar
    scalar_handle = [plt.Rectangle((0,0),1,1, color=colors[0])]
    scalar_label = ['Scalar']
    
    # Column 2: LANES (colors)
    lanes_values = sorted(df['LANES'].unique())
    lanes_handles = [plt.Rectangle((0,0),1,1, facecolor=colors.get(lanes, 'tab:gray')) 
                     for lanes in lanes_values]
    lanes_labels = [f'Lanes: {lanes}' for lanes in lanes_values]
    
    # Column 3: BUS_WIDTH (hatches)
    bus_width_values = sorted(df['BUS_WIDTH'].unique())
    bus_handles = [plt.Rectangle((0,0),1,1, facecolor='lightgray', 
                                 hatch=patterns.get(bus_width, '')*1, 
                                 edgecolor='black', ) 
                   for bus_width in bus_width_values]
    bus_labels = [f'Bus: {bus_width}' for bus_width in bus_width_values]
    
    # Position legends appropriately
    if use_broken_axis:
        legend_ax = ax_top
    else:
        legend_ax = main_ax
    
    # Create three separate legends (left to right: Scalar, Lanes, Bus)
    leg1 = legend_ax.legend(scalar_handle, scalar_label, loc='upper right', 
                           fontsize=18, frameon=True, bbox_to_anchor=(0.62, 1.0))
    legend_ax.add_artist(leg1)
    
    leg2 = legend_ax.legend(lanes_handles, lanes_labels, loc='upper right', 
                           fontsize=18, frameon=True, bbox_to_anchor=(0.81, 1.0))
    legend_ax.add_artist(leg2)
    
    leg3 = legend_ax.legend(bus_handles, bus_labels, loc='upper right', 
                           fontsize=18, frameon=True, bbox_to_anchor=(1.0, 1.0))

    # Customize the plot
    main_ax.set_xlabel('VLEN', fontsize=18,)

    if use_broken_axis:
        fig.text(0.04, 0.5, 'Cycles', va='center', rotation='vertical', fontsize=18,)
        ax_top.set_title(f'{benchmark} - Performance Analysis: Cycles vs VLEN', fontsize=16, fontweight='bold', pad=20)
    else:
        main_ax.set_ylabel('Cycles', fontsize=14, fontweight='bold')
        main_ax.set_title(f'{benchmark} - Performance Analysis: Cycles vs VLEN', fontsize=16, fontweight='bold', pad=20)

    # Set x-axis
    main_ax.set_xticks(vlen_tick_positions)
    main_ax.set_xticklabels(vlen_labels, fontsize=18)

    # Add grid
    main_ax.grid(True, axis='y')
    main_ax.set_axisbelow(True)

    if use_broken_axis:
        scalar_ax.grid(True, axis='y')
        scalar_ax.set_axisbelow(True)

    # Add value labels on bars
    # Scalar bar label
    if use_broken_axis:
        # Add label on the top part of the broken scalar bar
        ax_top.annotate(f'1x',
                xy=(scalar_x + bar_width/2, scalar_cycles),
                xytext=(0, 3),
                textcoords="offset points",
                ha='right', va='bottom',
                fontsize=15, fontweight='bold')
    else:
        scalar_ax.annotate(f'1x',
                xy=(scalar_x + bar_width/2, scalar_cycles),
                xytext=(0, 3),
                textcoords="offset points",
                ha='right', va='bottom',
                fontsize=15, fontweight='bold')

    # Vector bars labels
    for bar in bars_list:
        height = bar.get_height()
        if height > 0:  # Only add label if bar has height
            speedup = scalar_cycles / height
            main_ax.annotate(f'{speedup:.2f}x',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='left', va='bottom',
                    fontsize=14, fontweight='bold', rotation=45)

    # Improve layout
    plt.tight_layout()

    # Show the plot
    plt.show()
    plt.savefig(os.path.join(results_dir, f'{benchmark}.png'), dpi=300, bbox_inches='tight')

    print(f"✅ Successful Chart Generation for {benchmark}!!!\n")