#include "../libs/functions.hpp"

namespace x64
{
    std::unordered_map<uint8_t, std::function<void(uint64_t &, uint64_t)>> instructions = {
        {0x01, x64::mov},
        {0x02, x64::add},
        {0x03, x64::sub},
        {0x04, x64::mul},
        {0x05, x64::div},
        {0x06, x64::cmp},
        {0x07, x64::_and},
        {0x08, x64::_or},
        {0x09, x64::_xor},
        {0x0A, x64::_not},
        {0x0B, x64::jmp},
        {0x0C, x64::je},
        {0x0D, x64::jne},
        {0x0E, x64::jle},
        {0x0F, x64::jge},
        {0x10, x64::jl},
        {0x11, x64::jg},
        {0x12, x64::input},
        {0x13, x64::output},
        {0xFF, x64::breakpoint}};

    void setbit(uint16_t bitflag) { registers::flags |= bitflag; }
    void clearbit(uint16_t bitflag) { registers::flags &= ~bitflag; }
    void togglebit(uint16_t bitflag) { registers::flags ^= bitflag; }

    // lambda-based visitor
    void function(uint64_t &dest, uint64_t src, std::function<uint64_t(uint64_t &, uint64_t)> func)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t));
        value = func(dest, src);
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    // Arithmetic
    void add(uint64_t &dest, uint64_t src)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t)) + src;
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    void mov(uint64_t &dest, uint64_t src)
    {
        function(dest, src, [](uint64_t &dest, uint64_t src)
                 { return src; });
    }

    void sub(uint64_t &dest, uint64_t src)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t)) - src;
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    void mul(uint64_t &dest, uint64_t src)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t)) * src;
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    void div(uint64_t &dest, uint64_t src)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t)) / src;
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    // Assembly-type comparison using the 'flags' register
    void cmp(uint64_t &dest, uint64_t src)
    {
        if (dest == src)
        {
            // Set the zero flag to 1, the carry flag to 0
            registers::ZF = 1;
            registers::CF = 0;

            setbit(registers::ZF);
            clearbit(registers::CF);
        }
        else if (dest < src)
        {
            // Set the zero flag to 0, the carry flag to 1
            registers::ZF = 0;
            registers::CF = 1;

            clearbit(registers::ZF);
            setbit(registers::CF);
        }
        else if (dest > src)
        {
            // Set the zero flag to 0, the carry flag to 0
            registers::ZF = 0;
            registers::CF = 0;

            clearbit(registers::ZF);
            clearbit(registers::CF);
        }
    }

    // Bitwise
    void _and(uint64_t &dest, uint64_t src)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t)) & src;
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    void _or(uint64_t &dest, uint64_t src)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t)) | src;
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    void _xor(uint64_t &dest, uint64_t src)
    {
        uint64_t value = utils::read_bytes(dest, sizeof(uint64_t)) ^ src;
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    void _not(uint64_t &dest, uint64_t _)
    {
        uint64_t value = ~utils::read_bytes(dest, sizeof(uint64_t));
        utils::write_memory(dest, value, sizeof(uint64_t));
    }

    // Memory manipulation
    // void mov(uint64_t &dest, uint64_t src) { dest = src; }

    // Flow control
    void jmp(uint64_t &dest, uint64_t _) { registers::rip = dest; }
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

        utils::update_registers();

        std::cout << register_name + " = " << register_table.at(register_name) << std::endl;
    }

    void breakpoint(uint64_t &__, uint64_t _)
    {
        std::cout << "Breakpoint reached." << std::endl;
        std::cout << "RIP = " << registers::rip << std::endl;
        show_menu();
    }

    void show_menu()
    {
        std::printf("----- Debugging menu -----\n");
        std::printf("[1] Show registers\n");
        std::printf("[2] Show memory address value\n");
        std::printf("[3] Show memory address range\n");
        std::printf("[4] Show address space\n");
        std::printf("[5] Show flags\n");
        std::printf("[6] Print labels\n");
        std::printf("[7] Next instruction\n");
        std::printf("[8] Continue\n");
        std::printf("[9] List source code\n");
        std::printf("[0] Force quit\n");

        int choice;
        std::cout << "> ";
        std::cin >> choice;
        std::cin.ignore();

        std::vector<bool> flags_vector;
        std::bitset<16> flags(registers::flags);
        std::string flags_str;

        switch (choice)
        {
        case 1:
            std::printf("----- Registers -----\n");
            utils::update_registers();
            for (auto &reg : register_table)
            {
                std::cout << reg.first << " = " << *reg.second << ", offset: " << std::hex << static_cast<int>(register_offsets.at(reg.first)) << std::dec << std::endl;
            }
            break;
        case 2:
            std::printf("----- Memory address value -----\n");
            std::printf("Enter address: ");
            uint64_t address;
            std::cin >> address;
            std::cin.ignore();
            std::cout << std::hex << address << " = " << x64::memory[address] << std::endl;
            std::cout << std::dec;

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
                std::cout << std::hex << i << " = " << x64::memory[i] << std::endl;
            }

            std::cout << std::dec;
            break;

        case 4:
            std::printf("----- Memory -----\n");
            std::cout << std::hex;

            for (auto [k, v] : memory)
                std::cout << "0x" << k << " = " << static_cast<int>(v) << std::endl;

            std::cout << std::dec;
            break;

        case 5:
            std::printf("----- Flags -----\n");
            std::cout << "FLAGS: " << flags << std::endl;
            std::cout << "CF: " << flags[0] << std::endl;
            std::cout << "ZF: " << flags[1] << std::endl;
            break;

        case 6:
            std::printf("----- Labels -----\n");
            for (auto [k, v] : labels)
                std::cout << k << " = " << std::hex << v << std::dec << std::endl;

            break;

        case 7:
            x64::next();
            std::cout << "Next instruction executed, RIP = " << registers::rip << std::endl;
            break;

        case 8:
            std::cout << "Continuing..." << std::endl;
            return;

        case 9:
            std::printf("----- Source code -----\n");
            for (const auto &line : source)
                std::cout << line << std::endl;

            break;

        case 0:
            std::cout << "Quitting..." << std::endl;
            exit(0x01);

        default:
            std::cerr << "Invalid choice." << std::endl;
        }

        show_menu();
    }
}