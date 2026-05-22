from .vector_test import vector_test

class lmfrnet_test(vector_test):
    def __init__(self):
        super().init(
            name='lmfrnet',
            regex_pattern=r'The execution took (\d+) cycles\.'
        )