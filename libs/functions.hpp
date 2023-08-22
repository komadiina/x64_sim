#pragma once

#include <bitset>
#include <iostream>
#include <stdint.h>

#include "memory.hpp"
#include "utils.hpp"

namespace x64
{
    // Utility
    void setbit(uint16_t bitflag);
    void clearbit(uint16_t bitflag);
    void togglebit(uint16_t bitflag);

    // Arithmetic
    void add(uint64_t &dest, uint64_t src);
    void sub(uint64_t &dest, uint64_t src);
    void mul(uint64_t &dest, uint64_t src);
    void div(uint64_t &dest, uint64_t src);

    // Assembly-type comparison using 'flags' register
    void cmp(uint64_t &dest, uint64_t src);

    // Bitwise
    void _and(uint64_t &dest, uint64_t src);
    void _or(uint64_t &dest, uint64_t src);
    void _xor(uint64_t &dest, uint64_t src);
    void _not(uint64_t &dest, uint64_t _);

    // Memory manipulation
    void mov(uint64_t &dest, uint64_t src);

    // Flow control
    void jmp(uint64_t &dest, uint64_t _);
    void je(uint64_t &dest, uint64_t _);
    void jne(uint64_t &dest, uint64_t _);
    void jg(uint64_t &dest, uint64_t _);
    void jge(uint64_t &dest, uint64_t _);
    void jl(uint64_t &dest, uint64_t _);
    void jle(uint64_t &dest, uint64_t _);

    // I/O
    void input(uint64_t &dest, uint64_t src);
    void output(uint64_t &dest, uint64_t src);

    extern std::unordered_map<uint8_t, std::function<void(uint64_t &, uint64_t)>> instructions;

    void breakpoint(uint64_t &, uint64_t);
    void show_menu();
} // namespace x64