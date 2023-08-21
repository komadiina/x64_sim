#pragma once

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

#include "instruction.hpp"
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

    std::vector<std::string> fetch_code(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string line;

        uint16_t line_number = 1;
        std::vector<std::string> code;
        while (std::getline(file, line))
        {
            boost::to_lower(line);
            boost::algorithm::replace_all(line, ",", "");

            if (!lexer::lex_line(line))
            {
                throw std::invalid_argument("Invalid line " + std::to_string(line_number) + ": " + line);
            };

            code.push_back(line);
            line_number++;
        }

        file.close();
        return code;
    }

    void write_bytecode(const std::vector<std::string> &code)
    {
        std::vector<uint8_t> bytecode = {};

        for (const auto &line : code)
        {
            if (utils::is_label(line))
                labels[line.substr(0, line.size() - 1)] = registers::rip;
            else
                utils::write_bytes(Instruction::to_bytecode(Instruction(line)));
        }
    }

    Instruction interpret_bytes(const uint64_t &address)
    {
        std::vector<uint8_t> bytes = {};
        for (int i = 0; i < 8; i++)
            bytes.push_back(memory[address + i]);

        registers::rip += Instruction::NUM_BYTES;
        return Instruction(bytes);
    }

    void run()
    {
        registers::rip = 0;

        try
        {
            interpret_bytes(registers::rip).execute();
        }
        catch (...)
        { // x64::memory out_of_bounds exception (end of program)
        }

        std::cout << "<end>" << std::endl;
    }
}