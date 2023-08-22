#pragma once

#include <set>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "bytecode.hpp"
#include "memory.hpp"
#include "utils.hpp"

namespace x64
{
    class Instruction
    {
    public:
        const static int NUM_BYTES = 19; // 1 + 2 + 8 + 8

    private:
        std::string lexeme;
        uint8_t bytesign;
        uint8_t op1type, op2type;
        uint64_t op1value, op2value;

    public:
        Instruction(std::string lexeme)
        {
            this->lexeme = lexeme;

            // tokenize lexeme
            std::vector<std::string> tokens = {};
            boost::split(tokens, lexeme, boost::is_any_of(" "));

            if (tokens.size() == 1 && tokens[0] == "breakpoint")
            {
                bytesign = x64::bytesigns::breakpoint;
            }
            else if (tokens.size() == 2)
            {
                bytesign = x64::bytesigns::bytemap.at(tokens[0]);
                op1type = utils::get_operand_type(tokens[1]);
                op1value = utils::get_operand_value(op1type, tokens[1]);

                op2type = 0;
                op2value = 0;
            }
            else if (tokens.size() == 3)
            {
                bytesign = x64::bytesigns::bytemap.at(tokens[0]);

                op1type = utils::get_operand_type(tokens[1]);
                op1value = utils::get_operand_value(op1type, tokens[1]);

                op2type = utils::get_operand_type(tokens[2]);
                op2value = utils::get_operand_value(op2type, tokens[2]);
            }
            else
            {
                handle_error("Invalid instruction: " + lexeme);
                exit(0xFF);
            }
        }

        Instruction(const std::vector<uint8_t> &bytes)
        {
            bytesign = bytes[0];
            op1type = bytes[1];
            op2type = bytes[2];

            op1value = utils::to_int<uint64_t>(bytes, 3);
            op2value = utils::to_int<uint64_t>(bytes, 11);
        }

        static std::vector<uint8_t> to_bytecode(const Instruction &instr)
        {
            std::vector<uint8_t> bytecode = {instr.bytesign};
            bytecode.push_back(instr.op1type);
            bytecode.push_back(instr.op2type);

            std::vector<uint8_t> op1bytes = utils::to_bytes(instr.op1value);
            bytecode.insert(bytecode.end(), op1bytes.begin(), op1bytes.end());
            std::vector<uint8_t> op2bytes = utils::to_bytes(instr.op2value);
            bytecode.insert(bytecode.end(), op2bytes.begin(), op2bytes.end());

            return bytecode;
        }

        static Instruction interpret_bytes(const uint64_t &address)
        {
            std::vector<uint8_t> bytes = {};
            for (int i = 0; i < 8; i++)
                bytes.push_back(memory[address + i]);

            registers::rip += Instruction::NUM_BYTES;
            return Instruction(bytes);
        }

        void execute()
        {
        }

    private:
        void handle_error(const std::string &message)
        {
            std::cerr << message << std::endl;
            throw std::invalid_argument(message);
            exit(1);
        }
    };

    // 00_00 | 0000 0000 0000 0000 | 0000 0000 0000 0000 -> 18 bytes
    // instr_(op1type,op2type) | op1value | op2value
}