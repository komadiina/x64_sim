#include "../../libs/lexer.hpp"
#include <iostream>

int main() { std::cout << std::boolalpha << x64::lexer::lex_line("MOV rax, 15") << std::endl; }