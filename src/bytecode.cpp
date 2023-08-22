#include "../libs/bytecode.hpp"

namespace x64
{
    std::vector<std::string> fetch_code(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string line;

        uint16_t line_number = 1;
        std::vector<std::string> code;
        while (std::getline(file, line, '\n'))
        {
            std::string buf = line;
            buf = std::to_string(static_cast<int>(line_number)) + ": " + buf; // vuln to overflow violation
            source.push_back(buf);
            line_number++;

            if (line == "" || line[0] == ';' || line.empty())
                continue;

            if (!lexer::lex_line(line))
            {
                throw std::invalid_argument("Invalid line " + std::to_string(line_number) + ": " + line);
            };

            boost::to_lower(line);
            boost::algorithm::replace_all(line, ",", "");

            code.push_back(line);
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
            {
                utils::write_bytes(Instruction::to_bytecode(Instruction(line)), true);
            }
        }
    }

    void run()
    {
        registers::rip = CODE_START;

        while (registers::rip < memory.size())
            try
            {
                //     Instruction i = Instruction::interpret_bytes(registers::rip);
                //     std::cout << i << std::endl;
                //     i.execute();
                Instruction::interpret_bytes(registers::rip).execute();
            }
            catch (...)
            { // x64::memory out_of_bounds exception (end of program)
            }

        std::cout << "<end>" << std::endl;
    }
}