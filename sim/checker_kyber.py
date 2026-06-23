import re
import sys

KYBER_Q = 3329

# --- Funções de Referência (O Modelo Dourado baseado no seu C) ---

def ref_add(op1, op2):
    # Separa Low e High (16 bits)
    l1, h1 = op1 & 0xFFFF, (op1 >> 16) & 0xFFFF
    l2, h2 = op2 & 0xFFFF, (op2 >> 16) & 0xFFFF
    
    lr = (l1 + l2) % KYBER_Q
    hr = (h1 + h2) % KYBER_Q
    return (hr << 16) | lr

def ref_sub(op1, op2):
    l1, h1 = op1 & 0xFFFF, (op1 >> 16) & 0xFFFF
    l2, h2 = op2 & 0xFFFF, (op2 >> 16) & 0xFFFF
    
    lr = l1 - l2
    if lr < 0: lr += KYBER_Q
    
    hr = h1 - h2
    if hr < 0: hr += KYBER_Q
    
    return (hr << 16) | lr

def ref_mul(op1, op2):
    return (op1 * op2) % KYBER_Q

def ref_compress(coeff, d):
    # (((coeff << d) + KYBER_Q/2)/KYBER_Q) & ((1 << d) - 1)
    res = (((coeff << d) + (KYBER_Q // 2)) // KYBER_Q) & ((1 << d) - 1)
    return res

def ref_cbd2(i):
    low = ((i & 1) + ((i & 2) >> 1)) - (((i & 4) >> 2) + ((i & 8) >> 3))
    if low < 0: low += KYBER_Q
        
    high = (((i & 16) >> 4) + ((i & 32) >> 5)) - (((i & 64) >> 6) + ((i & 128) >> 7))
    if high < 0: high += KYBER_Q
        
    return (high << 16) | (low & 0xFFFF)

def ref_cbd3(i):
    low = ((i & 1) + ((i & 2) >> 1) + ((i & 4) >> 2)) - (((i & 8) >> 3) + ((i & 16) >> 4) + ((i & 32) >> 5))
    if low < 0: low += KYBER_Q
        
    high = (((i & 64) >> 6) + ((i & 128) >> 7) + ((i & 256) >> 8)) - (((i & 512) >> 9) + ((i & 1024) >> 10) + ((i & 2048) >> 11))
    if high < 0: high += KYBER_Q
        
    return (high << 16) | (low & 0xFFFF)

# --- Parser do Arquivo de Log ---

def main(logfile):
    # Padrão Regex para ler: [CHECKER] OPERACAO op1 e op2 = res
    # Ex: [CHECKER] KYBER_MUL      1f e 3a = 4c
    # Padrão Regex atualizado para ler o prefixo '0x'
    log_pattern = re.compile(r'\[CHECKER\]\s+(KYBER_\w+)\s+0x([0-9a-fA-F]+)\s+e\s+0x([0-9a-fA-F]+)\s+=\s+0x([0-9a-fA-F]+)')    
    pass_count = 0
    fail_count = 0
    line_num = 0

    try:
        with open(logfile, 'r') as f:
            for line in f:
                line_num += 1
                match = log_pattern.search(line)
                
                if match:
                    op_name = match.group(1)
                    op1 = int(match.group(2), 16)
                    op2 = int(match.group(3), 16)
                    hw_res = int(match.group(4), 16)
                    
                    ref_res = 0
                    
                    # Roteia para a função matemática correta
                    if op_name == "KYBER_ADD":
                        ref_res = ref_add(op1, op2)
                    elif op_name == "KYBER_SUB":
                        ref_res = ref_sub(op1, op2)
                    elif op_name == "KYBER_MUL":
                        ref_res = ref_mul(op1, op2)
                    elif op_name == "KYBER_COMPRESS":
                        ref_res = ref_compress(op1, op2) # op1 é coeff, op2 é 'd'
                    elif op_name == "KYBER_CBD2":
                        ref_res = ref_cbd2(op1) # cbd depende só do primeiro operando na sua arquitetura
                    elif op_name == "KYBER_CBD3":
                        ref_res = ref_cbd3(op1)
                    else:
                        continue # Operação desconhecida

                    # Compara Hardware vs Software
                    if hw_res == ref_res:
                        pass_count += 1
                    else:
                        fail_count += 1
                        print(f"❌ [ERRO] Linha {line_num} | {op_name}")
                        print(f"   Entradas : op1=0x{op1:x}, op2=0x{op2:x}")
                        print(f"   Hardware : 0x{hw_res:08x}")
                        print(f"   Esperado : 0x{ref_res:08x}\n")

    except FileNotFoundError:
        print(f"Erro: Arquivo '{logfile}' não encontrado.")
        return

    # Relatório Final
    print("="*40)
    print(" 🛡️  RELATÓRIO DE VERIFICAÇÃO KYBER")
    print("="*40)
    print(f" ✔️ SUCESSOS : {pass_count}")
    print(f" ❌ FALHAS   : {fail_count}")
    
    if fail_count == 0 and pass_count > 0:
        print("\n🎉 PARABÉNS! O hardware cravou 100% com o modelo em C.")
    elif pass_count == 0 and fail_count == 0:
        print("\n⚠️ Nenhum log do [CHECKER] foi encontrado no arquivo.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python3 checker_kyber.py <arquivo_de_log.txt>")
    else:
        main(sys.argv[1])