"""
    Base class for creating testcases
"""

import os
import re
import shutil
import subprocess

from concurrent.futures import ProcessPoolExecutor, as_completed
from abc import ABC, abstractmethod

from tqdm import tqdm

import csv

TEST_REGISTRY = {}

# Black Magic...
def register_test(cli_name):
    def wrapper(cls):
        TEST_REGISTRY[cli_name] = cls
        return cls
    return wrapper

class base_test(ABC):
    def __init__(self, name, regex_pattern=r''):
        script_dir = os.path.dirname(__file__)
        
        self.name = name
        self.app_dir = os.path.join (
            script_dir, '../../../app/', name
        )
        self.runs_dir = os.path.join (
            script_dir, '../runs'
        )

        self.testcase_root_dir = os.path.join (
            self.runs_dir, f'{self.name}'
        )

        self.sim_dir = os.path.join (
            script_dir, '../..'
        )

        self.pattern = re.compile(regex_pattern)

        self.params = []

    @abstractmethod
    def config(self):
        pass

    def gen_make_args(self, config):
        make_args = []

        for key, value in config.items():
            if key == 'id':
                continue

            elif key == 'LMUL':
                make_args.append(f'LMUL=m{value}')
            
            else:
                make_args.append(f'{key}={value}')
        
        return make_args

    def setup(self, config):
        id = config.get('id')
        config_dir = os.path.join (
            self.testcase_root_dir, id
        )
        
        config_app_dir = os.path.join (
            config_dir, self.name
        )

        def symlink_files(src, dst):
            os.symlink(os.path.abspath(src), dst)

        shutil.copytree (
            self.app_dir, 
            os.path.join (
                config_dir, self.name
            ),
            copy_function=symlink_files
        )

        shutil.copytree (
            os.path.join (
                self.app_dir, '../common'
            ),
            os.path.join (
                config_dir,
                'common'
            ),
            copy_function=symlink_files
        )

        return config_app_dir

    def compile(self, config, config_app_dir):
        id = config.get('id')

        make_args = self.gen_make_args(config)
        
        make = ['make', 'clean', 'all'] + make_args

        ret = subprocess.run (
            make,
            cwd=config_app_dir,
            capture_output=True,
            text=True
        )

        if ret.returncode == 0:
            return True, f'[+]: {id} compiled successfully'
        else:
            return False, f'[-]: {id} build failed\n{ret.stderr[:200]}'
        
    def simulate(self, config, config_app_dir):
        id = config.get('id')
        config_dir = os.path.join (
            self.testcase_root_dir, id
        )

        obj_dir = os.path.join (
            config_dir, 'obj_dir'
        )

        make_args = self.gen_make_args(config)

        verilator_args = make_args + [
            f'OBJ_DIR={obj_dir}',
            f'APP_DIR={config_app_dir}',
            f'VERILATOR_INPUT=parallel_tb.sv'
        ]

        verilator_cmd = [
            'make', 
            'clean', 
            'parallel_sim'
        ] + verilator_args

        ret = subprocess.run (
            verilator_cmd, 
            cwd=self.sim_dir, 
            capture_output=True, 
            text=True
        )

        log_path = os.path.join(config_dir, 'verilator.log')
        with open(log_path, 'w') as f:
            f.write(f"=== FULL COMMAND RUN ===\n{' '.join(verilator_cmd)}\n\n")
            f.write('=== STDOUT ===\n' + ret.stdout)
            f.write('=== STDERR ===\n' + ret.stderr)

        if ret.returncode == 0:
            match = self.pattern.search(ret.stdout)
            if match:
                cycles = int(match.group(1))
                return True, cycles, f'[+] {id}: simulation finished successfully'
            else:
                return False, None, f'[-] {id}: regex pattern not found in output (check {log_path})'
        else:
            return False, None, f'[-] {id}: simulation error (check {log_path})'
        

    def run_config(self, config):
        data = config.copy()
        data['test_name'] = self.name

        try:
            config_app_dir = self.setup(config)
            compile_success, compile_msg = self.compile (
                config, config_app_dir
            )

            if not compile_success:
                data['status'] = 'COMPILE_FAILED'
                data['cycles'] = 'NaN'
                data['message'] = compile_msg.strip()
                return data

            sim_success, cycles, sim_msg = self.simulate (
                config, config_app_dir
            )

            if sim_success:
                data['status'] = 'SUCCESS'
                data['cycles'] = cycles
                data['message'] = sim_msg.strip()
            else:
                data['status'] = 'SIM_FAILED'
                data['cycles'] = 'NaN'
                data['message'] = sim_msg.strip()

            return data
        
        except Exception as e:
            data['status'] = 'run_config() exception'
            data['cycles'] = 'NaN'
            data['message'] = str(e)
            return data
        
    def run(self, max_workers=8):
        if os.path.exists(self.testcase_root_dir):
            shutil.rmtree(self.testcase_root_dir)
        os.makedirs(self.testcase_root_dir, exist_ok=True)

        total_jobs = len(self.params)

        self.csv_path = os.path.join (
            self.runs_dir, self.name, 'results.csv'
        )

        self.params_names = list(self.params[0].keys()) + ['test_name', 'status', 'cycles', 'message']

        with open(self.csv_path, 'w', newline='') as csvfile:
            writer = csv.DictWriter(csvfile, fieldnames=self.params_names)
            writer.writeheader()

            with ProcessPoolExecutor(max_workers=max_workers) as executor:
                all_jobs = [
                    executor.submit(self.run_config, param)
                    for param in self.params
                ]

                # progress bar
                with tqdm(total=total_jobs, desc=f'Running {self.name}', unit='cfg') as pbar:
                    for j in as_completed(all_jobs):
                        result = j.result()
                        
                        writer.writerow(result)
                        csvfile.flush()

                        pbar.update(1)

    def clean(self):
        shutil.rmtree(self.testcase_root_dir)
            