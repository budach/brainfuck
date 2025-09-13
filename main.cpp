#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string load_file(const std::string& filename)
{
    // read entire text file into a string

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string minify(const std::string& code)
{
    const std::string valid_chars = "<>+-.,[]";
    std::string minified;
    minified.reserve(code.size());

    // only keep valid characters
    for (char c : code) {
        if (valid_chars.find(c) != std::string::npos) {
            minified += c;
        }
    }

    // replace "[-]" loops with new command 'Z'
    size_t idx = minified.find("[-]", 0);
    while (idx != std::string::npos) {
        minified.replace(idx, 3, "Z");
        idx = minified.find("[-]", idx + 1);
    }

    return minified;
}

std::vector<std::pair<char, int>> simplify_opcodes(const std::string& code)
{
    // merge consecutive commands into (command, count) pairs
    // only +, -, <, > are merged
    // for example "+++++>>>" becomes [('+', 5), ('>', 3)]

    // replace - with + and < with > and use negative counts
    // for example "-----" becomes [('+', -5)]

    // for loops pre-compute the jump target. that means for [ and ] store
    // the index of the matching bracket instead of the count

    std::vector<std::pair<char, int>> processed;
    std::vector<size_t> loop_stack; // to find matching brackets
    size_t idx = 0;
    size_t length = code.length();

    while (idx < length) {
        char current_char = code[idx];
        int count = 1;

        // only merge +, -, <, >
        if (current_char == '>' || current_char == '<' || current_char == '+' || current_char == '-') {
            while (idx + 1 < length && code[idx + 1] == current_char) {
                count++;
                idx++;
            }

            // flip sign for - and < to reduce number of commands
            if (current_char == '-') {
                current_char = '+';
                count = -count;
            } else if (current_char == '<') {
                current_char = '>';
                count = -count;
            }
        }

        processed.emplace_back(current_char, count);
        idx++;

        // take care of loops
        if (current_char == '[') {
            loop_stack.push_back(processed.size() - 1);
        } else if (current_char == ']') {
            if (loop_stack.empty()) {
                std::cerr << "Error: Unmatched ']'" << std::endl;
                exit(1);
            }
            size_t match_idx = loop_stack.back();
            loop_stack.pop_back();

            // replace count with jump target
            processed[match_idx].second = static_cast<int>(processed.size() - 1);
            processed[processed.size() - 1].second = static_cast<int>(match_idx);
        }
    }

    if (!loop_stack.empty()) {
        std::cerr << "Error: Unmatched '['" << std::endl;
        exit(1);
    }

    return processed;
}

void execute_code(const std::vector<std::pair<char, int>>& code)
{
    std::vector<unsigned char> data(30000, 0);
    size_t data_ptr = 0;
    size_t instr_ptr = 0;
    size_t code_length = code.size();

    while (instr_ptr < code_length) {
        char command = code[instr_ptr].first;
        int n = code[instr_ptr].second;

        if (command == '>') {
            data_ptr += n;
        } else if (command == '+') {
            data[data_ptr] = static_cast<unsigned char>(data[data_ptr] + n);
        } else if ((command == ']' && data[data_ptr] != 0) || (command == '[' && data[data_ptr] == 0)) {
            instr_ptr = n;
        } else if (command == 'Z') {
            data[data_ptr] = 0;
        } else if (command == '.') {
            std::cout << static_cast<char>(data[data_ptr]);
        } else if (command == ',') {
            char inp;
            std::cin.get(inp);
            data[data_ptr] = inp ? static_cast<unsigned char>(inp) : 0;
        }

        instr_ptr++;
    }
}

int main(int argc, const char* argv[])
{
    std::ios::sync_with_stdio(false);

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <bf_code_file>" << std::endl;
        return 1;
    }

    auto code = simplify_opcodes(minify(load_file(argv[1])));
    execute_code(code);

    return 0;
}