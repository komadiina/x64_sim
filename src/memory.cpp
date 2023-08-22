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
    } // namespace registers

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

    uint8_t LABEL = 0b00;
    uint8_t REGISTER = 0b01;
    uint8_t ADDRESS = 0b10;
    uint8_t IMMEDIATE = 0b11;
}