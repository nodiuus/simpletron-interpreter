#include <cctype>
#include <iostream>

#include "lexer.h"

lexer::lexer(const std::string &source) : source(source), pos(0), line(1), column(1) {
    initialize_keywords();
}

void lexer::initialize_keywords() {
    keywords = {
        {"READ", token_type::TOKEN_READ},
        {"WRITE", token_type::TOKEN_WRITE},
        {"LOAD", token_type::TOKEN_LOAD},
        {"STORE", token_type::TOKEN_STORE},
        {"ADD", token_type::TOKEN_ADD},
        {"SUB", token_type::TOKEN_SUB},
        {"DIVIDE", token_type::TOKEN_DIVIDE},
        {"MULTIPLY", token_type::TOKEN_MULTIPLY},
        {"BRANCH", token_type::TOKEN_BRANCH},
        {"BRANCH_NEGATIVE", token_type::TOKEN_BRANCHNEG},
        {"BRANCH_ZERO", token_type::TOKEN_BRANCHZERO},
        {"HALT", token_type::TOKEN_HALT}
    };
}

void lexer::skip_whitespace() {
    while (pos < source.size() && (source[pos] == ' ' || source[pos] == '\t' || source[pos] == '\n')) {
        if (source[pos] == '\n') {
            line++;
            column = 1;
        } else { 
            column++;
        }
        pos++;
    }  
}

token lexer::lex_identifier() {
    std::string identifier;

    while (pos < source.size() && std::isalnum(source[pos])) {
        identifier += source[pos];
        pos++;
        column++;
    }   
    auto it = keywords.find(identifier);
    if (it != keywords.end()) {
        return {it->second, identifier};
    } else {
        return {token_type::TOKEN_IDENTIFIER, identifier};
    }
}

token lexer::lex_number() {
    std::string result;
    while (pos < source.size() && std::isdigit(source[pos]) || source[pos] == '.') {
        result += source[pos];
        pos++;
    }

    return {token_type::TOKEN_OPERAND, result};
}

token lexer::next_token() {
    while (pos <= source.size() && std::isspace(source[pos])) {
        pos++;
    }    

    if (pos == source.length()) {
        std::cout << "EOF reached\n"; 
        return token(token_type::TOKEN_EOF);
    } 

    char current_character = source[pos];
    //std::cout << pos << " " << source.size() << std::endl;
    if (std::isdigit(current_character)) {
        return lex_number();
    } else if (std::isalpha(current_character)) {
        return lex_identifier();
    } else if (current_character == ';') {
        pos++;
        return token(token_type::TOKEN_SEMICOLON, ";");
    } else {
        pos++;
        return token(token_type::TOKEN_INVALID, std::string(1, current_character));
    }
}
