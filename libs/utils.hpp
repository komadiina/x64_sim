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
    std::vector<std::string> tokenize(std::string lexeme, std::string delim);

    bool is_label(const std::string &lexeme);

    uint8_t get_operand_type(const std::string &lexeme);

    uint64_t get_register_value(const std::string &target);

    uint64_t get_operand_value(uint8_t type, const std::string &lexeme);

    template <typename T>
    std::vector<uint8_t> to_bytes(T value, bool little_endian = true)
    {
        std::vector<uint8_t> bytes = {};
        for (int i = 0; i < sizeof(T); i++)
        {
            bytes.insert(bytes.begin(), static_cast<uint8_t>(value >> (i * 8)));

            if (!little_endian)
                std::reverse(bytes.begin(), bytes.end());
        }
        return bytes;
    }

    uint64_t write_bytes(const std::vector<uint8_t> &bytes);

    uint64_t read_bytes(const uint64_t &address, int num_bytes = 8, bool little_endian = true);

    template <typename T>
    T to_int(const std::vector<uint8_t> &bytes, int start)
    {
        T value = T{0};
        for (int i = 0; i < sizeof(T); i++)
            value |= bytes[start + i] << (i * 8);

        return value;
    }
}