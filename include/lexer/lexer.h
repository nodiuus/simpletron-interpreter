#pragma once
#include <map>
#include <string>

enum class token_type {
    TOKEN_READ = 10,
    TOKEN_WRITE = 11,
    TOKEN_LOAD = 20,
    TOKEN_STORE = 21,
    TOKEN_ADD = 30,
    TOKEN_SUB = 31,
    TOKEN_DIVIDE = 32,
    TOKEN_MULTIPLY = 33,
    TOKEN_BRANCH = 40,
    TOKEN_BRANCHNEG = 41,
    TOKEN_BRANCHZERO = 42,
    TOKEN_HALT = 43,
    TOKEN_SEMICOLON = 44,
    TOKEN_COMMENT = 50,
    TOKEN_IDENTIFIER = 51,
    TOKEN_OPERAND = 52,
    TOKEN_INVALID = 53,
    TOKEN_EOF = 54
};

/*
class token {
    token_type type;
    std::string value;
    int line;
    int column;
};
*/

struct token {
    token_type type;
    std::string value;
};

class lexer {
public:
    lexer(const std::string &source);
    token next_token();
    token lex_identifier();
    token lex_number();

    void skip_whitespace();
    void initialize_keywords();
private:
    const std::string source;
    int pos;
    int line;
    int column;

    std::map<std::string, token_type> keywords;
};
