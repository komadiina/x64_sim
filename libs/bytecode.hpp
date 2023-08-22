#pragma once

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <deque>

#include "functions.hpp"
#include "lexing.hpp"
#include "memory.hpp"

#include <boost/algorithm/string.hpp>

namespace x64
{
    namespace bytesigns
    {
        const uint8_t mov = 0x01;
        const uint8_t add = 0x02;
        const uint8_t sub = 0x03;
        const uint8_t mul = 0x04;
        const uint8_t div = 0x05;
        const uint8_t cmp = 0x06;
        const uint8_t _and = 0x07;
        const uint8_t _or = 0x08;
        const uint8_t _xor = 0x09;
        const uint8_t _not = 0x0A;
        const uint8_t jmp = 0x0B;
        const uint8_t je = 0x0C;
        const uint8_t jne = 0x0D;
        const uint8_t jle = 0x0E;
        const uint8_t jge = 0x0F;
        const uint8_t jl = 0x10;
        const uint8_t jg = 0x11;
        const uint8_t input = 0x12;
        const uint8_t output = 0x13;
        const uint8_t breakpoint = 0xFF;

        const std::map<std::string, uint8_t> bytemap = {
            {"mov", mov},
            {"add", add},
            {"sub", sub},
            {"mul", mul},
            {"div", div},
            {"cmp", cmp},
            {"and", _and},
            {"or", _or},
            {"xor", _xor},
            {"not", _not},
            {"jmp", jmp},
            {"je", je},
            {"jne", jne},
            {"jle", jle},
            {"jge", jge},
            {"jl", jl},
            {"jg", jg},
            {"in", input},
            {"out", output},
            {"breakpoint", breakpoint}};
    };
    
    extern std::vector<std::string> source;

    std::vector<std::string> fetch_code(const std::string &filename);
    void write_bytecode(const std::vector<std::string> &code);
    // Instruction interpret_bytes(const uint64_t &address);
    void run();
}

#include "instruction.hpp"