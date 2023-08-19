#include <iomanip>
#include <iostream>

#include "../../libs/encoding.hpp"
#include "../../libs/functions.hpp"
#include "../../libs/vars.hpp"

int main() {
	x64::bytecode::initialize();
	x64::registers::rax	 = 0x00'00'00'00'00'00'01'23;
	x64::labels["start"] = 0x1122AAFF;
	auto instr			 = x64::bytecode::get_instruction("jmp start");
	auto bytes			 = x64::bytecode::encode(instr);

	std::cout << "instr.second.size(): " << instr.second.size() << std::endl;
	std::cout << "instr.second[0].type(): " << x64::operand_types[instr.second[0].type()]
			  << std::endl;
	std::cout << "instr.second[0].value(): " << instr.second[0].value() << std::endl;
	for (const auto& [k, v] : x64::labels)
		std::cout << "label: " << k << ", value: " << v << std::endl;

	std::cout << std::hex << "rip: " << x64::registers::rip << std::endl;
	x64::registers::rip = x64::bytecode::write_bytecode(bytes, x64::registers::rip);

	for (const auto& [k, v] : x64::memory)
		std::cout << "0x" << std::setw(8) << std::setfill('0') << k << ": " << std::setw(2)
				  << std::to_integer<int>(v) << std::endl;

	std::cout << "rip: " << x64::registers::rip << std::endl;

	return EXIT_SUCCESS;
}