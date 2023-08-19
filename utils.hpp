#pragma once

#include <iostream>
#include <map>
#include <stdint.h>
#include <string>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>

#include "memory.hpp"

namespace x64::utils {
    std::vector<std::string> tokenize(std::string lexeme, std::string delim) {
        std::vector<std::string> tokens = {};
        boost::split(tokens, lexeme, boost::is_any_of(delim));
        return tokens;
    }
    
    uint8_t get_operand_type(const std::string& lexeme) {
        if (lexeme[0] == 'R' || lexeme[0] == 'r') {
            return x64::REGISTER;
        } else if (lexeme[0] == '[') {
            return x64::ADDRESS;
        } else if (lexeme[lexeme.size() - 1] != ':') {
            return x64::IMMEDIATE;
        } else
            return x64::LABEL;
    }
    
    uint64_t get_register_value(const std::string& target) {
        return *x64::register_table[target];
    }
    
    uint64_t get_operand_value(uint8_t type, const std::string& lexeme) {
        if (type == x64::IMMEDIATE)
            return stoi(lexeme, nullptr, 10);
        else if (type == x64::REGISTER)
            return get_register_value(lexeme);
        
    }
}