#pragma once
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

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
    virtual_machine() : memory(MEM_SIZE), accumulator(0), instruction_register(0), program_counter(0) {}

    void read() {
        std::cout << "Enter an integer: "; 
        std::cin >> memory[operand];
    }

    void write() {
        std::cout << memory[operand] << '\n'; 
    }

    void load() {
        accumulator = memory[operand];
    }

    void store() {
        memory[operand] = accumulator;
    }

    void add() {
        accumulator += memory[operand];
    }

    void subtract() {
        accumulator -= memory[operand];
    }

    void divide() {
        accumulator /= memory[operand];
    }

    void multiply() {
        accumulator *= memory[operand];
    }

    void branch() {
        program_counter = operand - 1;
    }

    void branch_negative() {
       if (accumulator < 0) {
            program_counter = operand - 1;
       }
    }

    void branch_zero() {
       if (accumulator == 0) {
            program_counter = operand - 1;
       }
    }
    void reset_machine() {
        accumulator = 0;
        program_counter = 0;
        instruction_register = 0;
        
        for (int i = 0; i < MEM_SIZE; i++) {
            memory[i] = 0;
        }
    }
    
    void load_program(std::vector<int> program) {
        if (program.size() <= memory.size()) {
            std::copy(program.begin(), program.end(), memory.begin());
        } else {
            std::cerr << "too large for memory" << std::endl;
        }
    }


    void execute_program() {
        while (program_counter < memory.size()) {
            instruction_register = memory[program_counter];

            opcode = instruction_register / 100; //extracts opcode from the first two numbers
            operand = instruction_register % 100; //extracts operand from the last two numbers

            switch (opcode) {
                case READ:
                    read();
                    break;
                case WRITE:
                    write();
                    break;
                case LOAD:
                    load();
                    break;
                case STORE:
                    store();
                    break;
                case ADD:
                    add();
                    break;
                case SUB:
                    subtract();
                    break;
                case DIVIDE:
                    divide();
                    break;
                case MULTIPLY:
                    multiply();
                    break;
                case BRANCH:
                    branch();
                    break;
                case BRANCHNEG:
                    branch_negative();
                    break;
                case BRANCHZERO:
                    branch_zero();
                    break;
                case HALT:
                    std::cout << "HALTED" << '\n';
                    return;
                default:
                    std::cout << "invalid opcode, fuck you " << opcode << '\n';
                    return;
            }
            program_counter++;

            if (program_counter >= memory.size()) {
                std::cout << "Program counter out of bounds, terminating program." << '\n';
                 break;
            }
        }
    };
private:
    static const int MEM_SIZE = 1000;
    std::vector<int> memory;
    int program_counter;
    int accumulator;
    int instruction_register;
    int opcode;
    int operand;
};
