import os
import sys
import importlib
import argparse
import pkgutil

from tests.base_test import TEST_REGISTRY

def load_tests():
    for _, module_name, _ in pkgutil.iter_modules(['tests']):
        importlib.import_module(f'tests.{module_name}')

def main():
    load_tests()

    parser = argparse.ArgumentParser (
        description='RS5 Vector Parallel Simulation Environment'
    )

    parser.add_argument (
        '--test', 
        type=str, 
        required=True,
        # choices=TEST_REGISTRY.keys(),
        # help=f"Available tests: {', '.join(TEST_REGISTRY.keys())}"
        help='Specify which testcase to run'
    )

    parser.add_argument('--workers', type=int, default=8)
    parser.add_argument('--run', action='store_true')
    parser.add_argument('--clean', action='store_true')

    args = parser.parse_args()

    if args.test not in TEST_REGISTRY:
        print(f"[!] Error: '{args.test}' is not a valid test")
        print(f"[i] Available tests: \n\t{',\n\t'.join(TEST_REGISTRY.keys())}")
        sys.exit(1)

    testcase = TEST_REGISTRY[args.test]()

    if args.clean:
        print(f'[!] Cleaning directories for {testcase.name}...')
        testcase.clean()

    if args.run:
        print(f'[*] Starting {testcase.name} simulation with {args.workers} workers...')
        testcase.run(max_workers=args.workers)

if __name__ == '__main__':
    main()
