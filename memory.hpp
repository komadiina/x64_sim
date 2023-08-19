#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <stdint.h>

namespace x64
{
    extern uint64_t rax, rbx, rcx, rdx;
    extern uint64_t rip, rsp;
    extern uint64_t r1, r2, r3, r4;

    // Flags register
    extern uint16_t flags;

    // carry, parity, adjust, zero, sign, trap, interrupt, direction, overflow
    extern uint16_t CF, PF, AF, ZF, SF, TF, IF, DF, OF;

    extern std::map<uint64_t, std::byte> memory;
    extern std::map<std::string, uint64_t> labels;
    extern std::unordered_map<std::string, uint64_t*> register_table;

    extern uint8_t LABEL = 0b00;
    extern uint8_t REGISTER = 0b01;
    extern uint8_t ADDRESS = 0b10;
    extern uint8_t IMMEDIATE = 0b11;
}