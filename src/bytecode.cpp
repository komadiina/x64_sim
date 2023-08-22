#include "../libs/bytecode.hpp"

namespace x64
{
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

    /*
    Instruction interpret_bytes(const uint64_t &address)
    {
        std::vector<uint8_t> bytes = {};
        for (int i = 0; i < 8; i++)
            bytes.push_back(memory[address + i]);

        registers::rip += Instruction::NUM_BYTES;
        return Instruction(bytes);
    }
    */

    void run()
    {
        registers::rip = 0;

        try
        {
            Instruction::interpret_bytes(registers::rip).execute();
        }
        catch (...)
        { // x64::memory out_of_bounds exception (end of program)
        }

        std::cout << "<end>" << std::endl;
    }
}