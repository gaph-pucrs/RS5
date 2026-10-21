import re
from collections import defaultdict

def parse_riscv_instructions(file_path):
    instruction_counts = defaultdict(int)

    # Regular expression to match instructions
    instruction_regex = re.compile(r'\s+[0-9a-f]+:\s+[0-9a-f]+\s+([a-z]+)')

    with open(file_path, 'r') as file:
        for line in file:
            match = instruction_regex.search(line)
            if match:
                instruction = match.group(1)
                instruction_counts[instruction] += 1

    return instruction_counts

def main():
    file_path = 'test.lst'  # Change this to the path of your .lst file
    instruction_counts = parse_riscv_instructions(file_path)

    for instruction, count in sorted(instruction_counts.items()):
        print(f'{instruction}: {count}')

if __name__ == "__main__":
    main()
