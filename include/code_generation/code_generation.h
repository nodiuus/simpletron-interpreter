#pragma once
#include <vector>
#include <string>
#include <memory>

#include "parser.h"

class code_generator {
public:
    explicit code_generator(const program& program);
    std::vector<int> generate_code();

private:
    const program& program_;
    int generate_instruction(const instruction& instr);
};

