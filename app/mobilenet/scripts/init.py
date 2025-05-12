import os
import sys
import subprocess

python_ver = 'python3'
params_dir = '../params/'
scripts_dir = 'scripts'
files = ['image.py', 'weights.py']

if not os.path.exists (params_dir):
    subprocess.run(['mkdir', params_dir])

type = ''
if len(sys.argv) > 1:
    type = sys.argv[1]
else:
    # type : operations domain: int, float, double, long, ...
    print(f"Usage: {python_ver} init.py <type>")
    print(f"Setting type = float by default.")
    type = 'float'

for filename in files:
    if (os.path.isfile(filename)):
        subprocess.run([python_ver, filename, type])
    else:
        print(f"(!) Script does not exist in '{scripts_dir}' directory.")
