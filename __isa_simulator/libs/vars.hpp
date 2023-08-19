#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "./memory_manip.hpp"
#include "./string_manip.hpp"

namespace x64 {

	extern std::map<uint64_t, std::byte> memory;
	extern std::map<std::string, uint64_t> labels;
	extern std::unordered_map<std::string, uint8_t> register_ids;
	extern std::unordered_map<std::string, uint64_t*> register_table;

	extern std::set<std::string> instruction_set;

	extern uint8_t REGISTER;
	extern uint8_t ADDRESS;
	extern uint8_t IMMEDIATE;
	extern uint8_t LABEL;
	extern std::unordered_map<uint8_t, std::string> operand_types;

	namespace bytecode {
		extern std::map<std::string, uint8_t> instruction_ids;
		extern bool is_initialized;
	} // namespace bytecode

	namespace registers {
		extern uint64_t rax, rbx, rcx, rdx;
		extern uint64_t rip, rsp;
		extern uint64_t r1, r2, r3, r4;

		// Flags register
		extern uint16_t flags;

		// carry, parity, adjust, zero, sign, trap, interrupt, direction, overflow
		extern uint16_t CF, PF, AF, ZF, SF, TF, IF, DF, OF;
	} // namespace registers

	// Operand class, represents an operand in an instruction
	class operand {
		private:
			// Lexical value of the operand
			std::string _lexeme;

			// Type of the operand, 0b01 for register, 0b10 for memory, 0b11 for immediate
			std::uint8_t _type;

			// Value of the operand or the pointed address
			std::uint64_t _value;

			// If _type is ADDRESS
			std::uint64_t _pointer;

			// Whether the operand has been used or not
			// Used in encoding.hpp -> bytecode map
			mutable bool used = false;
			std::string _token;

		public:
			operand(const std::string& lexeme, std::uint8_t type, std::uint64_t value);
			operand(std::string lexeme);

			// Getters
			inline std::string lexeme() const { return _lexeme; }
			inline std::uint8_t type() const { return _type; }
			inline std::uint64_t value() const { return _value; }
			inline std::string token() const { return _token; }
			inline std::uint64_t pointer() const { return _pointer; }

			// Non-const getters
			inline std::string& lexeme() { return _lexeme; }
			inline std::uint8_t& type() { return _type; }
			inline std::uint64_t& value() { return _value; }
			inline std::uint64_t& pointer() { return _pointer; }
			inline std::string& token() { return _token; }

			// Setters
			inline void lexeme(const std::string& lexeme) { _lexeme = lexeme; }
			inline void type(std::uint8_t type) { _type = type; }
			inline void value(std::uint64_t value) { _value = value; }
	};

	// Shorthanding a function of variable arg. size
	using instruction = std::pair<std::byte, std::vector<operand>>;

	using bytes = std::vector<std::byte>;
} // namespace x64
