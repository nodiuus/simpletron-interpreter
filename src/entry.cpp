#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "lexer.h"
#include "parser.h"
#include "virtual_machine.h"
#include "code_generation.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string source;
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        source += line + "\n";
    }
    file.close();

    lexer lex(source);
    parser parser(lex);

    try {
        auto program = parser.parse_program();
        program_validator::validate(*program);

        code_generator generator(*program);
        auto instructions = generator.generate_code();

        virtual_machine vm;
        vm.load_program(instructions);
        vm.execute_program();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
