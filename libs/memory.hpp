#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <stdint.h>

namespace x64
{
    namespace registers
    {
        extern uint64_t rax, rbx, rcx, rdx;
        extern uint64_t rip, rsp;
        extern uint64_t r1, r2, r3, r4;
        extern uint64_t rio; // I/O ports

        // Flags register
        extern uint16_t flags;

        // carry, parity, adjust, zero, sign, trap, interrupt, direction, overflow
        extern uint16_t CF, PF, AF, ZF, SF, TF, IF, DF, OF;
    } // namespace registers

    extern std::map<uint64_t, uint8_t> memory;
    extern std::map<std::string, uint64_t> labels;
    extern std::unordered_map<std::string, uint64_t *> register_table;

    extern uint8_t LABEL;
    extern uint8_t REGISTER;
    extern uint8_t ADDRESS;
    extern uint8_t IMMEDIATE;
}