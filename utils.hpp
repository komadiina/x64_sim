#pragma once

#include <iostream>
#include <map>
#include <stdint.h>
#include <string>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>

#include "memory.hpp"

namespace x64::utils
{
    std::vector<std::string> tokenize(std::string lexeme, std::string delim)
    {
        std::vector<std::string> tokens = {};
        boost::split(tokens, lexeme, boost::is_any_of(delim));
        return tokens;
    }

    bool is_label(const std::string &lexeme)
    {
        return lexeme[lexeme.size() - 1] == ':';
    }

    uint8_t get_operand_type(const std::string &lexeme)
    {
        if (lexeme[0] == 'R' || lexeme[0] == 'r')
        {
            return x64::REGISTER;
        }
        else if (lexeme[0] == '[')
        {
            return x64::ADDRESS;
        }
        else if (lexeme[lexeme.size() - 1] != ':')
        {
            return x64::IMMEDIATE;
        }
        else
            return x64::LABEL;
    }

    uint64_t get_register_value(const std::string &target)
    {
        return *x64::register_table[target];
    }

    uint64_t get_operand_value(uint8_t type, const std::string &lexeme)
    {
        if (type == x64::IMMEDIATE)
            return stoi(lexeme, nullptr, 10);
        else if (type == x64::REGISTER)
            return get_register_value(lexeme);
    }

    template <typename T>
    std::vector<uint8_t> to_bytes(T value)
    {
        std::vector<uint8_t> bytes = {};
        for (int i = 0; i < sizeof(T); i++)
        {
            bytes.push_back((value >> (i * 8)) & 0xFF);
        }
        return bytes;
    }

    uint64_t write_bytes(const std::vector<uint8_t> &bytes)
    {
        for (uint8_t byte : bytes)
            memory[registers::rip++] = byte;

        // RIP always hold the address of the next instruction while running the current instruction.
        return registers::rip;
    }

    template <typename T>
    T to_int(const std::vector<uint8_t> &bytes, int start)
    {
        T value = T{0};
        for (int i = 0; i < sizeof(T); i++)
            value |= bytes[start + i] << (i * 8);

        return value;
    }
}