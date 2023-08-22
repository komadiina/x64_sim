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
    for (const auto &l : code)
        std::cout << l << std::endl;

    x64::write_bytecode(code);

    std::cout << "---- LABELS ----" << std::endl;

    for (const auto &[k, v] : x64::labels)
        std::cout << k << ": " << v << std::endl;

    std::cout << "---- MEMORY ----" << std::endl;
    std::cout << std::hex;
    for (const auto &[k, v] : x64::memory)
        std::cout << k << ": " << static_cast<int>(v) << std::endl;
    std::cout << std::dec;

    std::cout << x64::utils::read_bytes(0x0b, 8, true) << std::endl;

    x64::run();

    return 0;
}