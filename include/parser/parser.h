#pragma once
#include <vector>
#include <string>
#include <memory>

#include "lexer.h"

class ast_node {
public:
    virtual ~ast_node() = default;
};

class statement : public ast_node {
public:
    virtual ~statement() = default;
};

class instruction : public statement {
public:
    token_type operation;
    std::string operand;

    instruction(token_type op, const std::string& opnd = "");
};


class program : public ast_node {
public:
    std::vector<std::unique_ptr<statement>> statements;
};

class parser {
public:
    explicit parser(lexer& lex);
    std::unique_ptr<program> parse_program();

private:
    lexer& lexer_;
    token current_token_;

    void advance();
    void expect(token_type type);
    std::unique_ptr<statement> parse_statement();
    std::unique_ptr<instruction> parse_instruction();
};

class program_validator {
public:
    static void validate(const program& program);

private:
    static void validate_instruction_operands(const instruction& instruction);
};
