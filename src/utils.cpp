#include "../libs/utils.hpp"

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

    bool is_numerical(const std::string &lexeme)
    {
        for (char c : lexeme)
            if (!isdigit(c))
                return false;
        return true;
    }

    uint8_t get_operand_type(const std::string &lexeme)
    {
        if (lexeme[0] == 'R' || lexeme[0] == 'r')
        {
            return x64::REGISTER;
        }
        else if (lexeme[0] == '_')
            return x64::LABEL;
        else if (lexeme[0] == '[')
        {
            return x64::ADDRESS;
        }
        else if (is_numerical(lexeme))
        {
            return x64::IMMEDIATE;
        }
    }

    uint64_t get_register_value(const std::string &target)
    {
        // std::cout << target << " = " << *x64::register_table[target] << std::endl;
        return *x64::register_table[target];
    }

    uint64_t get_operand_value(uint8_t type, const std::string &lexeme)
    {
        if (type == x64::IMMEDIATE)
        {
            std::cout << lexeme << std::endl;
            return stoi(lexeme, nullptr, 10);
        }
        else if (type == x64::REGISTER)
            return get_register_value(lexeme);
        else if (type == x64::LABEL)
            return x64::labels[lexeme];
        else // register addressing
            return read_bytes(get_register_value(lexeme.substr(1, lexeme.size() - 2)), 8);
    }

    uint64_t read_bytes(const uint64_t &address, int num_bytes, bool little_endian)
    {
        std::vector<uint8_t> bytes = {};
        for (std::size_t ip = 0; ip < num_bytes; ++ip)
            bytes.insert(bytes.begin(), x64::memory[address + ip * 0x01]);

        if (!little_endian)
            std::reverse(bytes.begin(), bytes.end());

        uint64_t value = 0LL;
        for (int i = 0; i < num_bytes; i++)
            value |= static_cast<uint64_t>(bytes[i]) << (i * 8);

        return value;
    }

    uint64_t write_bytes(const std::vector<uint8_t> &bytes)
    {
        for (uint8_t byte : bytes)
            memory[registers::rip++] = byte;

        // RIP always hold the address of the next instruction while running the current instruction.
        return registers::rip;
    }
}