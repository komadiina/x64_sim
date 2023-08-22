#include "../libs/memory.hpp"

namespace x64
{
    namespace registers
    {
        uint64_t rax, rbx, rcx, rdx;
        uint64_t rip, rsp;
        uint64_t r1, r2, r3, r4;
        uint64_t rio; // I/O ports

        // Flags register
        uint16_t flags;

        // carry, parity, adjust, zero, sign, trap, interrupt, direction, overflow
        uint16_t CF, PF, AF, ZF, SF, TF, IF, DF, OF;

        uint8_t offset = 8; // 8 bytes
    }                       // namespace registers

    std::map<uint64_t, uint8_t> memory;
    std::map<std::string, uint64_t> labels;
    std::unordered_map<std::string, uint64_t *> register_table = {
        {"rax", &registers::rax},
        {"rbx", &registers::rbx},
        {"rcx", &registers::rcx},
        {"rdx", &registers::rdx},
        {"rip", &registers::rip},
        {"rsp", &registers::rsp},
        {"r1", &registers::r1},
        {"r2", &registers::r2},
        {"r3", &registers::r3},
        {"r4", &registers::r4},
        {"rio", &registers::rio}};

    std::unordered_map<std::string, uint8_t> register_offsets = {
        {"rax", 0},
        {"rbx", 8},
        {"rcx", 16},
        {"rdx", 24},
        {"rip", 32},
        {"rsp", 40},
        {"r1", 48},
        {"r2", 56},
        {"r3", 64},
        {"r4", 72},
        {"rio", 80}};
        
    std::vector<std::string> source = {};

    uint64_t CODE_START = 0x100;

    uint8_t NONE = 0b0000;
    uint8_t REGISTER = 0b0001;
    uint8_t ADDRESS = 0b0010;
    uint8_t IMMEDIATE = 0b0011;
    uint8_t LABEL = 0b0100;

    void init_registers()
    {
        registers::rip = CODE_START;
        for (int i = 0; i < CODE_START; i++)
            memory[i] = 0x0;

        for (const auto &[reg, offset] : register_offsets)
            for (int i = offset; i < offset + 8; i++)
                memory[i] = 0x0;
    }
}