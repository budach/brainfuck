import sys

OPCODE_MAP = {
    ">": 0,
    "+": 1,
    "[": 2,
    "]": 3,
    "Z": 4,
    ".": 5,
    ",": 6,
}


def annotate_loops(code):
    # pre-compute jump targets for loops

    code_length = len(code)
    stack = []  # to find matching brackets
    i = 0

    while i < code_length:
        command, _ = code[i]

        match command:
            case "[":
                stack.append(i)
            case "]":
                if not stack:
                    raise ValueError("Unmatched '['")
                start = stack.pop()
                code[start] = ("[", i)
                code[i] = ("]", start)
            case _:
                pass

        i += 1

    if stack:
        raise ValueError("Unmatched '['")

    return code


def replace_cmds_with_num(code):
    # comparing integers is faster than comparing characters in Python
    # will be used in the main execution loop later
    return [(OPCODE_MAP[cmd], n) for cmd, n in code]


def load_and_preprocess_code(file_name):
    with open(file_name, "rt") as file:
        # minify code and replace clear loops with new command "Z"
        code = "".join(c for c in file.read() if c in ("><+-.,[]")).replace("[-]", "Z")

    # merge consecutive commands into (command, count) tuples
    # replace "-" with "+", "<" with ">" to make opcode main loop smaller later
    code_length = len(code)
    processed_code = []
    i = 0

    while i < code_length:
        char = code[i]
        if char in "<>+-":
            count = 1
            while i + 1 < code_length and code[i + 1] == char:
                count += 1
                i += 1
            if char == "-":
                processed_code.append(("+", -count))
            elif char == "<":
                processed_code.append((">", -count))
            else:
                processed_code.append((char, count))
        else:
            processed_code.append((char, 1))
        i += 1

    return processed_code


def execute_bf(code):
    data = [0] * 30000
    data_ptr = 0
    instr_ptr = 0
    code_length = len(code)

    # if-else is still faster than match-case
    # matching order in if-else matters as well
    # matching enums or any kind of indirection is A LOT slower (just Python things)
    while instr_ptr < code_length:
        command, n = code[instr_ptr]

        if command == 0:  # ">"
            data_ptr += n
        elif command == 1:  # "+"
            data[data_ptr] = (data[data_ptr] + n) & 0xFF
        elif (command == 3 and data[data_ptr] != 0) or (  # "]"
            command == 2 and data[data_ptr] == 0  # "["
        ):
            instr_ptr = n
        elif command == 4:  # "Z"
            data[data_ptr] = 0
        elif command == 5:  # "."
            sys.stdout.write(chr(data[data_ptr]))
        elif command == 6:  # ","
            inp = sys.stdin.read(1)
            data[data_ptr] = ord(inp) if inp else 0

        instr_ptr += 1


def main(input_file):
    code = load_and_preprocess_code(input_file)
    code = annotate_loops(code)
    code = replace_cmds_with_num(code)
    execute_bf(code)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python main.py <bf_code_file>")
        sys.exit(1)
    main(sys.argv[1])
