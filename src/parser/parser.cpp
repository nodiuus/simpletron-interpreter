#include <stdexcept>

#include "parser.h"

instruction::instruction(token_type op, const std::string& opnd)
    : operation(op), operand(opnd) {}

parser::parser(lexer& lex) 
    : lexer_(lex), current_token_{token_type::TOKEN_INVALID, ""} {
    advance(); // Get first token
}

void parser::advance() {
    current_token_ = lexer_.next_token();
}

void parser::expect(token_type type) {
    if (current_token_.type != type) {
        throw std::runtime_error("Unexpected token: " + current_token_.value);
    }
    advance();
}

std::unique_ptr<program> parser::parse_program() {
    auto prog = std::make_unique<program>();
    
    while (current_token_.type != token_type::TOKEN_EOF) {
        auto stmt = parse_statement();
        if (stmt) {
            prog->statements.push_back(std::move(stmt));
        }
    }
    
    return prog;
}

std::unique_ptr<statement> parser::parse_statement() {
    // Skip any invalid tokens
    while (current_token_.type == token_type::TOKEN_INVALID) {
        advance();
    }

    // Handle EOF
    if (current_token_.type == token_type::TOKEN_EOF) {
        return nullptr;
    }

    auto stmt = parse_instruction();
    
    // Each instruction should be followed by a semicolon
    if (current_token_.type == token_type::TOKEN_SEMICOLON) {
        advance();
    }

    return stmt;
}

std::unique_ptr<instruction> parser::parse_instruction() {
    token_type operation = current_token_.type;
    std::string operand;

    // Check if the token is a valid instruction
    switch (operation) {
        case token_type::TOKEN_READ:
        case token_type::TOKEN_WRITE:
        case token_type::TOKEN_LOAD:
        case token_type::TOKEN_STORE:
        case token_type::TOKEN_ADD:
        case token_type::TOKEN_SUB:
        case token_type::TOKEN_DIVIDE:
        case token_type::TOKEN_MULTIPLY:
        case token_type::TOKEN_BRANCH:
        case token_type::TOKEN_BRANCHNEG:
        case token_type::TOKEN_BRANCHZERO:
        case token_type::TOKEN_HALT:
            advance(); // Consume the instruction token
            
            // Check if there's an operand
            if (current_token_.type == token_type::TOKEN_OPERAND ||
                current_token_.type == token_type::TOKEN_IDENTIFIER) {
                operand = current_token_.value;
                advance(); // Consume the operand
            }
            
            return std::make_unique<instruction>(operation, operand);
            
        default:
            throw std::runtime_error("Invalid instruction: " + current_token_.value);
    }
}

void program_validator::validate(const program& prog) {
    bool has_halt = false;
    
    for (const auto& stmt : prog.statements) {
        if (auto inst = dynamic_cast<const instruction*>(stmt.get())) {
            if (inst->operation == token_type::TOKEN_HALT) {
                has_halt = true;
            }
            
            // Validate that instructions that require operands have them
            validate_instruction_operands(*inst);
        }
    }
    
    if (!has_halt) {
        throw std::runtime_error("Program must end with HALT instruction");
    }
}

void program_validator::validate_instruction_operands(const instruction& inst) {
    bool requires_operand = inst.operation != token_type::TOKEN_HALT;
    
    if (requires_operand && inst.operand.empty()) {
        throw std::runtime_error("Instruction requires an operand");
    }
}
