#pragma once

#include <iostream>
#include <stdint.h>
#include "memory.hpp"
#include "utils.hpp"

#include <boost/variant/variant.hpp>

class Instruction;

namespace x64
{
    // Utility
    void setbit(uint16_t bitflag);
    void clearbit(uint16_t bitflag);

    void setflag(uint16_t flag);
    void toggleflag(uint16_t flag);

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
    void _not(uint64_t &dest);

    // Memory manipulation
    void mov(uint64_t &dest, uint64_t src);

    // Flow control
    void jmp(uint64_t &dest);
    void je(uint64_t &dest);
    void jne(uint64_t &dest);
    void jg(uint64_t &dest);
    void jge(uint64_t &dest);
    void jl(uint64_t &dest);
    void jle(uint64_t &dest);

    // I/O
    void input(uint64_t &dest);
    void output(uint64_t &dest);

    void breakpoint();

    // "interpreter"
    void run(const Instruction &instr);

} // namespace x64