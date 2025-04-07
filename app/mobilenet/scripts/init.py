import os
import subprocess

python_ver = 'python3'
params_dir = '../params/'
# scripts_dir = '/sim/RS5/app/tiny-ml/mobilenet/py/v2/scripts'
scripts_dir = 'scripts'
files = ['image.py', 'weights.py']

if not os.path.exists (params_dir):
    subprocess.run(['mkdir', params_dir])

for filename in files:
    # filepath = os.path.join(scripts_dir, filename)
    # if (os.path.isfile(filepath)):
    if (os.path.isfile(filename)):
        # subprocess.run([python_ver, filepath])
        subprocess.run([python_ver, filename])
    else:
        print(f"(!) Script does not exist in '{scripts_dir}' directory.")
