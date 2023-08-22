#pragma once

#include <iostream>
#include <map>
#include <stdint.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
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

    uint64_t write_bytes(std::vector<uint8_t> bytes, bool little_endian = true);

    uint64_t read_bytes(const uint64_t &address, int num_bytes = 8, bool little_endian = true);

    template <typename T>
    T to_int(std::vector<uint8_t> bytes, int start, bool little_endian = true)
    {
        if (!little_endian)
            std::reverse(bytes.begin(), bytes.end());

        T value = T{0};
        for (int i = 0; i < sizeof(T); i++)
            value |= bytes[start + i] << (i * 8);

        return value;
    }

    template <typename T>
    std::vector<uint8_t> to_bytes(T value)
    {
        std::vector<uint8_t> byte_vector;
        for (std::size_t i = 0; i < sizeof(value); ++i)
            byte_vector.insert(byte_vector.begin(),
                               static_cast<uint8_t>(std::byte{value >> (i * 8)}));
        return byte_vector;
    }

    uint64_t write_memory(uint64_t address, uint64_t value, uint8_t num_bytes = sizeof(uint64_t));
    void update_registers();
}