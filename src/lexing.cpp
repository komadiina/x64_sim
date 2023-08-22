#include "../libs/lexing.hpp"

namespace x64::lexer {
    bool lex_line(std::string line)
    {
        auto it = line.begin();
        return qi::phrase_parse(it, line.end(), grammar::instruction, qi::space);
    }

    bool lex_file(std::string filename)
    {
        std::ifstream file(filename);
        std::string line;
        size_t lineno = 1;

        while (std::getline(file, line))
        {
            if (!lex_line(line))
                throw std::invalid_argument("Invalid line " + str(lineno) + ": " + line);
            lineno++;
        }

        file.close();
        return true;
    }
}