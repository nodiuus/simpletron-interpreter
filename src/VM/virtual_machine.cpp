#include "virtual_machine.h"

virtual_machine::virtual_machine()
    : memory(MEM_SIZE), accumulator(0), instruction_register(0), program_counter(0) {}

void virtual_machine::read() {
    std::cout << "Enter an integer: ";
    std::cin >> memory[operand];
}

void virtual_machine::write() {
    std::cout << memory[operand] << '\n';
}

void virtual_machine::load() {
    accumulator = memory[operand];
}

void virtual_machine::store() {
    memory[operand] = accumulator;
}

void virtual_machine::add() {
    accumulator += memory[operand];
}

void virtual_machine::subtract() {
    accumulator -= memory[operand];
}

void virtual_machine::divide() {
    accumulator /= memory[operand];
}

void virtual_machine::multiply() {
    accumulator *= memory[operand];
}

void virtual_machine::branch() {
    program_counter = operand - 1;
}

void virtual_machine::branch_negative() {
    if (accumulator < 0) {
        program_counter = operand - 1;
    }
}

void virtual_machine::branch_zero() {
    if (accumulator == 0) {
        program_counter = operand - 1;
    }
}

void virtual_machine::reset_machine() {
    accumulator = 0;
    program_counter = 0;
    instruction_register = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i] = 0;
    }
}

void virtual_machine::load_program(std::vector<int> program) {
    if (program.size() <= memory.size()) {
        std::copy(program.begin(), program.end(), memory.begin());
    } else {
        std::cerr << "too large for memory" << std::endl;
    }
}

void virtual_machine::execute_program() {
    while (program_counter < memory.size()) {
        instruction_register = memory[program_counter];

        opcode = instruction_register / 100; // Extracts opcode from the first two numbers
        operand = instruction_register % 100; // Extracts operand from the last two numbers

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
}

