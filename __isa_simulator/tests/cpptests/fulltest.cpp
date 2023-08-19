#include <iomanip>
#include <iostream>

#include "../../libs/encoding.hpp"
#include "../../libs/files.hpp"
#include "../../libs/functions.hpp"
#include "../../libs/vars.hpp"

int main(int argC, char** argV) {
	x64::bytecode::initialize();

	auto instructions_vec = x64::utils::read_file(argV[1]);

	for (const auto& instr : instructions_vec)
		std::cout << instr << std::endl;

	for (const auto& instr : instructions_vec) {
		auto instr_pair		= x64::bytecode::get_instruction(instr);
		auto bytes			= x64::bytecode::encode(instr_pair);
		x64::registers::rip = x64::bytecode::write_bytecode(bytes, x64::registers::rip);
	}

	for (const auto& [k, v] : x64::memory)
		std::cout << "0x" << std::setw(8) << std::setfill('0') << k << ": " << std::setw(2)
				  << std::to_integer<int>(v) << std::endl;

	return EXIT_SUCCESS;
}