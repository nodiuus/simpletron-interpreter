#pragma once
#include <cctype>
#include <vector>
#include <iostream>

enum opcodes {
    READ = 10,
    WRITE = 11,
    LOAD = 20,
    STORE = 21,
    ADD = 30,
    SUB = 31,
    DIVIDE = 32,
    MULTIPLY = 33,
    BRANCH = 40,
    BRANCHNEG = 41,
    BRANCHZERO = 42,
    HALT = 43
};

class virtual_machine {
public:
    virtual_machine();

    void read();
    void write();
    void load();
    void store();
    void add();
    void subtract();
    void divide();
    void multiply();
    void branch();
    void branch_negative();
    void branch_zero();
    void reset_machine();
    void load_program(std::vector<int> program);
    void execute_program();

private:
    static const int MEM_SIZE = 1000;
    std::vector<int> memory;
    int program_counter;
    int accumulator;
    int instruction_register;
    int opcode;
    int operand;
};


