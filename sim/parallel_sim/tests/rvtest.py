from .vector_test import vector_test

class rvtest_test(vector_test):
    def __init__(self):
        super().__init__(
            name='riscv-tests',
            regex_pattern=r'The execution took (\d+) cycles\.'
        )