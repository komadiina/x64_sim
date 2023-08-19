#pragma once

#include <iostream>
#include <stdint.h>

#include "memory.hpp"
#include "utils.hpp"

namespace x64
{
    class Operand
    {
    private:
        std::string lexeme;
        uint8_t type;
        uint64_t value, pointer;

    public:
        Operand(std::string lexeme, uint8_t type, uint64_t value, uint64_t pointer)
        {
            this->lexeme = lexeme;
            this->type = type;
            this->value = value;
            this->pointer = pointer;
        }

        Operand(std::string lexeme)
        {
            init(lexeme);
        }

        std::string getLexeme() { return this->lexeme; }
        uint8_t getType() { return this->type; }
        uint64_t getValue() { return this->value; }
        uint64_t getPointer() { return this->pointer; }

        void setLexeme(std::string lexeme) { this->lexeme = lexeme; }
        void setType(uint8_t type) { this->type = type; }
        void setValue(uint64_t value) { this->value = value; }
        void setPointer(uint64_t pointer) { this->pointer = pointer; }

    private:
        void init(std::string lexeme)
        {
            this->lexeme = lexeme;
            type = utils::get_operand_type(lexeme);
            
        }
    };

    // 00_00 | 0000 0000 0000 0000 | 0000 0000 0000 0000 -> 18 bytes
    // instr_(op1type,op2type) | op1value | op2value
}