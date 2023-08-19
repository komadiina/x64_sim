#pragma once

#include <set>
#include "operand.hpp"

#include <boost/algorithm/string.hpp>

namespace x64
{
    extern std::set<std::string> instruction_set;

    class Instruction
    {
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
            
            // if label (size == 1)
            if (tokens.size() == 1) {
                if (tokens[0][tokens[0].size() - 1] == ':') {
                    // put the label in the labels map
                    std::string label = tokens[0].substr(0, tokens[0].size() - 1);
                    labels[label] = rip;
                }
                else if (tokens[0] == "BRK") {
                        
                } else if (tokens[0] == "INPUT") {
                    
                }
            }            
            else if (tokens.size() == 2) {
                
            } else if (tokens.size() == 3) {
                
            }
        }
    };

    // 00_00 | 0000 0000 0000 0000 | 0000 0000 0000 0000 -> 18 bytes
    // instr_(op1type,op2type) | op1value | op2value
}