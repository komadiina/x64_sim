#include "../libs/memory.hpp"
#include "../libs/bytecode.hpp"
#include "../libs/functions.hpp"
#include "../libs/lexing.hpp"
#include "../libs/utils.hpp"
#include "../libs/instruction.hpp"

#include <iostream>

int main(int argC, char **argV)
{
    if (argC != 2)
    {
        std::cout << "Usage: sim.exe <file>.asm" << std::endl;
        exit(1);
    }

    x64::init_registers();
    std::string target_file = argV[1];
    std::vector<std::string> code = x64::fetch_code(target_file);
    x64::write_bytecode(code);
    x64::run();

    return 0;
}