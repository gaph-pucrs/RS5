def mac(op_a, op_b, accum, bits=34):
    # simula signed 17 bits
    def to_signed17(x):
        x = x & 0x1FFFF
        if x & 0x10000:
            x -= 0x20000
        return x
    
    # simula signed 35 bits
    def to_signed35(x):
        x = x & 0x7FFFFFFFF
        if x & 0x400000000:
            x -= 0x800000000
        return x
    
    a = to_signed17(op_a)
    b = to_signed17(op_b)
    c = to_signed35(accum)
    result = a * b + c
    return result & 0x7FFFFFFFF  # trunca para 35 bits

def mul32_5039(temp0):
    temp0 = temp0 & 0xFFFFFFFF
    
    # Ciclo 1: LOW
    low_result = mac(temp0 & 0xFFFF, 5039, 0)
    
    # Ciclo 2: HIGH  
    high_result = mac((temp0 >> 16) & 0xFFFF, 5039, 0)
    
    # combina
    result = (high_result << 16) + low_result
    return result

# testa
for temp0 in [0x27D9, 0x4a11, 0x0001, 0xD00, 0xFFFFFFFF]:
    got = mul32_5039(temp0)
    expected = temp0 * 5039
    status = "PASS" if got == expected else "FAIL"
    print(f"temp0=0x{temp0:08X}  expected=0x{expected:X}  got=0x{got:X}  [{status}]")