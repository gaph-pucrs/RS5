import os
# from tests.base_test import base_test
from tests.lmfrnet_test import lmfrnet_test
from tests.rvtest import rvtest_test

script_dir = os.path.dirname(__file__)
runs_dir = os.path.join(script_dir, 'runs')

os.makedirs(runs_dir, exist_ok=True)

# x = lmfrnet_test()
x = rvtest_test()

print('run')
# input()
print('running...')
x.run(12)

print('clean')
input()
print('cleaning...')
x.clean()
