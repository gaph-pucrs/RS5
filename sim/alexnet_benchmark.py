import os
import subprocess
import shutil

# *********************************
# PARAMS
# *********************************
VLENs = [0, 64, 128, 256]  # 0 = scalar (no vector extension)

print(f'\nAlexNet CNN Benchmark')
print(f'\tVLENs = {VLENs}')
print()

# *********************************
# Paths
# *********************************
script_dir  = os.path.dirname(os.path.abspath(__file__))
cnn_dir     = os.path.join(script_dir, "../app/alexnet_layers")
results_dir = os.path.join(cnn_dir, "results")

layers = ["conv1", "conv2", "conv3", "conv4", "conv5", "fc"]

print('Layers that will be executed:')
for i, layer in enumerate(layers):
    print(f'\t{i+1})', layer)
print()

# *********************************
# Execution
# *********************************
for layer in layers:
    print("\n*********************************")
    print(f'Starting execution of {layer}.')
    print("*********************************")

    layer_path   = os.path.join(cnn_dir, layer)
    layer_results = os.path.join(results_dir, layer)

    if os.path.exists(layer_results):
        shutil.rmtree(layer_results)
    os.makedirs(layer_results)
    os.makedirs(os.path.join(script_dir, "results"), exist_ok=True)

    ###############
    # Compile + Run per VLEN
    ###############
    for vlen in VLENs:
        print(f'\n  VLEN={vlen}')

        make_log = os.path.join(layer_results, f"make_vlen{vlen}.txt")
        try:
            with open(make_log, "w") as f:
                subprocess.run(['make', '-C', layer_path, 'clean', 'all', f'VLEN={vlen}'],
                               check=True, stdout=f, stderr=subprocess.STDOUT,
                               universal_newlines=True)
            print(f"    ✅ Compiled")
        except subprocess.CalledProcessError:
            print(f"    ❌ Compilation failed (see {make_log})")
            continue

        bin_path    = f"../app/alexnet_layers/{layer}/{layer}.bin"
        vlen_tag    = "scalar" if vlen == 0 else f"vlen{vlen}"
        result_path = os.path.join(layer_results, f"{vlen_tag}.txt")

        print(f"    Simulating {vlen_tag} ... ", end="", flush=True)

        venable = 0 if vlen == 0 else 1
        make_cmd = [
            'make', '-C', script_dir,
            f'VENABLE={venable}',
            f'VLEN={vlen}',
            f'BIN_FILE_PATH={bin_path}',
        ]

        with open(result_path, "w") as f:
            try:
                subprocess.run(make_cmd, check=True, stdout=f, stderr=f,
                               universal_newlines=True)
                print("✅")
            except subprocess.CalledProcessError:
                print("❌")
                continue

        # Keep the profiling report (sim/results is wiped on every run)
        report_src = os.path.join(script_dir, "results", "Report.txt")
        if os.path.exists(report_src):
            shutil.copy(report_src, os.path.join(layer_results, f"{vlen_tag}_report.txt"))

        with open(result_path, "r") as f:
            content = f.read()
        # Failed if the log reports a failure or the program never reached its end
        if "fail" in content.lower() or f"Fim {layer}" not in content:
            os.rename(result_path, os.path.join(layer_results, f"[fail]{vlen_tag}.txt"))
            print(f"    ❌ Program did not finish correctly (see [fail]{vlen_tag}.txt)")
        else:
            print(f"    Saved {os.path.relpath(result_path, script_dir)}")
