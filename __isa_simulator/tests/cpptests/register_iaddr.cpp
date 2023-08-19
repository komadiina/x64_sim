#include <iostream>

#include "../../libs/encoding.hpp"
#include "../../libs/files.hpp"
#include "../../libs/functions.hpp"
#include "../../libs/lexer.hpp"
#include "../../libs/vars.hpp"

int main(int argC, char** argV) {
	std::string line = "MOV [rax], rbx";

	x64::registers::rax = 0xAABBCCDD;
	x64::registers::rbx = 0x11223344;
	std::cout << std::hex << "rax: " << x64::registers::rax << std::endl;
	std::cout << std::hex << "rbx: " << x64::registers::rbx << std::endl;

	// [rax], write zeroes
	x64::utils::write_bytes(x64::registers::rax, 0x1234567890, 8);
	for (const auto& [k, v] : x64::memory)
		std::cout << std::hex << k << ": " << std::to_integer<int>(v) << std::endl;

	std::cout << std::hex << "[rax]: " << x64::utils::read_bytes(x64::registers::rax, 8)
			  << std::endl;

	auto instr = x64::bytecode::get_instruction(line);
	std::cout << std::boolalpha << x64::lexer::lex_line(line) << std::endl;

	std::cout << std::to_integer<int>(instr.first) << std::endl;
	std::cout << instr.second[0].token() << ", " << instr.second[0].value() << ", "
			  << (uint16_t)instr.second[0].type() << std::endl;
	std::cout << "reg ptr: " << instr.second[1].pointer() << std::endl;

	std::cout << instr.second[1].token() << ", " << instr.second[1].value() << ", "
			  << (uint16_t)instr.second[1].type() << std::endl;

	return EXIT_SUCCESS;
}