import os
from .base_test import base_test

class lmfrnet_test(base_test):
    def __init__(self):
        super().__init__(
            name='lmfrnet',
            regex_pattern=r'The execution took (\d+) cycles\.'
        )

        self.VLENs = [64, 128, 256]
        self.LMULs = [1, 2, 4, 8]
        self.BUS_WIDTHs = [32, 64, 128, 256]

        self.params = self.config()

    def config(self):
        jobs = []
        for vlen in self.VLENs:
            for lmul in self.LMULs:
                for bus_width in self.BUS_WIDTHs:
                    LANES = [
                        2**i for i in range((vlen//32).bit_length()) 
                            if 2**i <= (vlen//32)
                    ] 

                    for lanes in LANES:
                        llen = vlen // lanes
                        id = f'v{vlen}_m{lmul}_b{bus_width}_l{lanes}'

                        jobs.append({
                            'id': id,
                            'VENABLE': '1',
                            'VLEN': vlen,
                            'LMUL': lmul, 
                            'BUS_WIDTH': bus_width,
                            'LLEN': llen
                        })
                        
        return jobs