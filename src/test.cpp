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
    auto code = x64::fetch_code("ex.asm");
    x64::write_bytecode(code);
    x64::run();
}