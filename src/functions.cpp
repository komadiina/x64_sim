#include "../libs/functions.hpp"

namespace x64
{
    void setbit(uint16_t bitflag) { registers::flags |= bitflag; }
    void clearbit(uint16_t bitflag) { registers::flags &= ~bitflag; }

    void setflag(uint16_t flag) { registers::flags |= flag; }
    void toggleflag(uint16_t flag) { registers::flags ^= flag; }

    // Arithmetic
    void add(uint64_t &dest, uint64_t src) { dest += src; }
    void sub(uint64_t &dest, uint64_t src) { dest -= src; }
    void mul(uint64_t &dest, uint64_t src) { dest *= src; }
    void div(uint64_t &dest, uint64_t src) { dest /= src; }

    // Assembly-type comparison using 'flags' register
    void cmp(uint64_t &dest, uint64_t src)
    {
        if (dest == src)
        {
            // Set the zero flag to 1, the carry flag to 0
            setbit(registers::ZF);
            clearbit(registers::CF);
        }
        else if (dest < src)
        {
            // Set the zero flag to 0, the carry flag to 1
            clearbit(registers::ZF);
            setbit(registers::CF);
        }
        else if (dest > src)
        {
            // Set the zero flag to 0, the carry flag to 0
            clearbit(registers::ZF);
            clearbit(registers::CF);
        }
    }

    // Bitwise
    void _and(uint64_t &dest, uint64_t src) { dest &= src; }
    void _or(uint64_t &dest, uint64_t src) { dest |= src; }
    void _xor(uint64_t &dest, uint64_t src) { dest ^= src; }
    void _not(uint64_t &dest) { dest = ~dest; }

    // Memory manipulation
    void mov(uint64_t &dest, uint64_t src) { dest = src; }

    // Flow control
    void jmp(uint64_t &dest, uint64_t _) { registers::rip = dest; } // or ++dest?
    void je(uint64_t &dest, uint64_t _)
    {
        if (registers::flags & registers::ZF && !(registers::flags & registers::CF))
            jmp(dest, _);
    }
    void jne(uint64_t &dest, uint64_t _)
    {
        if (!(registers::flags & registers::ZF))
            jmp(dest, _);
    }
    void jg(uint64_t &dest, uint64_t _)
    {
        if (!(registers::flags & registers::ZF) && !(registers::flags & registers::CF))
            jmp(dest, _);
    }
    void jge(uint64_t &dest, uint64_t _)
    {
        if (!(registers::flags & registers::CF))
            jmp(dest, _);
    }
    void jl(uint64_t &dest, uint64_t _)
    {
        if (registers::flags & registers::CF && !(registers::flags & registers::ZF))
            jmp(dest, _);
    }
    void jle(uint64_t &dest, uint64_t _)
    {
        if (registers::flags & registers::ZF || registers::flags & registers::CF)
            jmp(dest, _);
    }

    // I/O
    void input(uint64_t &dest, uint64_t _)
    {
        uint64_t value = 0LLU;
        std::cout << "> ";
        std::cin >> value;
        std::cin.ignore(); // newline

        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    void output(uint64_t &__, uint64_t _)
    {
        std::string register_name;
        std::cin >> register_name;
        std::cin.ignore(); // newline

        std::cout << register_name + " = " << register_table.at(register_name) << std::endl;
    }

    void breakpoint()
    {
        std::cout << "Breakpoint reached." << std::endl;
        // TODO
        show_menu();
    }

    void show_menu()
    {
        std::printf("----- Debugging menu -----\n");
        std::printf("[1] Show registers\n");
        std::printf("[2] Show memory address value\n");
        std::printf("[3] Show memory address range\n");
        std::printf("[4] Show flags\n");
        std::printf("[5] Next instruction\n");
        std::printf("[6] Continue\n");

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            std::printf("----- Registers -----\n");
            for (auto &reg : register_table)
            {
                std::cout << reg.first << " = " << reg.second << std::endl;
            }
            break;
        case 2:
            std::printf("----- Memory address value -----\n");
            std::printf("Enter address: ");
            uint64_t address;
            std::cin >> address;
            std::cin.ignore();
            std::cout << "Value at address " << address << " = " << utils::read_bytes(address) << std::endl;
            break;

        case 3:
            std::printf("----- Memory address range -----\n");
            std::printf("Enter start address: ");
            uint64_t start_address;
            std::cin >> start_address;
            std::cin.ignore();
            std::printf("Enter end address: ");
            uint64_t end_address;
            std::cin >> end_address;
            std::cin.ignore();
            std::printf("----- Memory address range -----\n");
            for (uint64_t i = start_address; i < end_address; i++)
            {
                std::cout << "Value at address " << i << " = " << utils::read_bytes(i) << std::endl;
            }
            break;
        case 4:
            std::printf("----- Flags -----\n");
            std::bitset<16> flags(registers::flags);
            flags.to_string();
            std::vector<bool> flags_vector;
            for (int i = 0; i < 16; i++)
                flags_vector.push_back(flags[i]);

            std::cout << "CF | PF | AF | ZF | SF | TF | IF | DF | OF" << std::endl;
            for (bool flag : flags_vector)
                std::cout << flag << "  | ";

        case 5:
            // TOOD
            break;
        case 6:
            // TODO
            break;
        default:
            std::cerr << "Invalid choice." << std::endl;
        }
    }
}