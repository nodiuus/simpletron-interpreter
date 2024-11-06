#include <stdexcept>

#include "code_generation.h"

code_generator::code_generator(const program& program)
    : program_(program) {}

std::vector<int> code_generator::generate_code() {
    std::vector<int> instructions;
    for (const auto& stmt : program_.statements) {
        if (auto instr = dynamic_cast<const instruction*>(stmt.get())) {
            instructions.push_back(generate_instruction(*instr));
        }
    }
    return instructions;
}

int code_generator::generate_instruction(const instruction& instr) {
    int code = 0;
    switch (instr.operation) {
        case token_type::TOKEN_READ:
            code = 1000 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_WRITE:
            code = 1100 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_LOAD:
            code = 2000 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_STORE:
            code = 2100 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_ADD:
            code = 3000 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_SUB:
            code = 3100 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_DIVIDE:
            code = 3200 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_MULTIPLY:
            code = 3300 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_BRANCH:
            code = 4000 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_BRANCHNEG:
            code = 4100 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_BRANCHZERO:
            code = 4200 + std::stoi(instr.operand);
            break;
        case token_type::TOKEN_HALT:
            code = 4300;
            break;
        default:
            throw std::runtime_error("Unsupported instruction: " + instr.operand);
    }
    return code;
}
