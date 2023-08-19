#include <bitset>
#include <iostream>

#include "../../libs/encoding.hpp"
#include "../../libs/functions.hpp"
#include "../../libs/lexer.hpp"
#include "../../libs/vars.hpp"

int main() {
	// TODO: Implement the following bytecode representation
	// bytecode format: 0xIIYZ;
	// II: instruction id
	// Y: operand1 type
	// Z: operand2 type

	x64::bytecode::initialize();
	std::cout << std::hex << std::endl;

	for (const auto& [key, value] : x64::bytecode::instruction_ids) {
		std::cout << key << ": " << std::to_integer<int>(std::byte{value}) << std::endl;
	}

	x64::registers::rax = 0x0000000000000123;
	x64::registers::rbx = 0x0000000000000456;

	std::cout << std::hex << "rax: 0x" << x64::registers::rax << std::endl;
	std::cout << std::hex << "rbx: 0x" << x64::registers::rbx << std::endl;

	x64::instruction instr = x64::bytecode::get_instruction("mov rax, rbx");
	std::cout << std::to_integer<int>(instr.first) << std::endl;
	std::cout << instr.second[0].value() << std::endl;
	std::cout << instr.second[1].value() << std::endl;

	std::cout << "------------------" << std::endl;

	// Proper fetching of register values
	x64::registers::rax = 0x000000000000001A;
	auto rax_op			= x64::operand("rax");

	std::cout << std::hex << "0x" << x64::registers::flags << std::endl;

	std::cout << std::hex << "0x" << x64::registers::rax << std::endl;
	std::cout << std::hex << "0x" << rax_op.value() << std::endl;

	// Flags register validation (using cmp)
	x64::registers::flags = 0x0;
	x64::registers::flags &= x64::registers::ZF;
	std::cout << std::hex << "0x" << x64::registers::flags << std::endl;
	std::cout << "0b" << std::bitset<16>(x64::registers::flags) << std::endl;

	std::cout << "------------------" << std::endl;

	uint64_t a = 1LL, b = 2LL, c = 1LL;

	x64::cmp(a, b);
	std::cout << "0b" << std::bitset<16>(x64::registers::flags) << std::endl;

	x64::cmp(a, c);
	std::cout << "0b" << std::bitset<16>(x64::registers::flags) << std::endl;

	x64::cmp(b, c);
	std::cout << "0b" << std::bitset<16>(x64::registers::flags) << std::endl;
}