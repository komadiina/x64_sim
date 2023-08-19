#include "../libs/vars.hpp"

namespace x64 {
	namespace registers {
		uint64_t rax, rbx, rcx, rdx;
		uint64_t rip = 0xFFFF, rsp;
		uint64_t r1, r2, r3, r4;

		// Flags register
		uint16_t flags = 0;

		// flags register masks
		uint16_t CF = 0x0001;
		uint16_t PF = 0x0004;
		uint16_t AF = 0x0010;
		uint16_t ZF = 0x0040;
		uint16_t SF = 0x0080;
		uint16_t TF = 0x0100;
		uint16_t IF = 0x0200;
		uint16_t DF = 0x0400;
		uint16_t OF = 0x0800;
	} // namespace registers

	std::map<uint64_t, std::byte> memory;
	std::map<std::string, uint64_t> labels;

	std::unordered_map<std::string, uint8_t> register_ids = {
		{"rax", 0x00},
		{"rbx", 0x01},
		{"rcx", 0x02},
		{"rdx", 0x03},
		{"rip", 0x04},
		{"rsp", 0x05},
		{"r1",  0x06},
		{"r2",  0x07},
		{"r3",  0x08},
		{"r4",  0x09},
	};

	std::unordered_map<std::string, uint64_t*> register_table = {
		{"rax", &registers::rax},
		{"rbx", &registers::rbx},
		{"rcx", &registers::rcx},
		{"rdx", &registers::rdx},
		{"rip", &registers::rip},
		{"rsp", &registers::rsp},
		{"r1",  &registers::r1 },
		{"r2",  &registers::r2 },
		{"r3",  &registers::r3 },
		{"r4",  &registers::r4 }
	  };

	// clang-format off
	std::set<std::string> instruction_set = {
        "add","sub","div","mul","cmp","and","or","xor",
        "not","mov","jmp","je","jne","jg","jge","jl",
        "jle",
	};
	// clang-format on

	// ------------------------- Operand types -------------------------- //

	uint8_t REGISTER  = 0b01;
	uint8_t ADDRESS	  = 0b10;
	uint8_t IMMEDIATE = 0b11;
	uint8_t LABEL	  = 0xFF;

	std::unordered_map<uint8_t, std::string> operand_types = {
		{REGISTER,  "register" },
		{ADDRESS,	  "address"  },
		{IMMEDIATE, "immediate"},
		{LABEL,		"label"	   },
	};

	// ----------------------- Bytecode namespace ----------------------- //

	namespace bytecode {
		std::map<std::string, uint8_t> instruction_ids;
		bool is_initialized = false;
	} // namespace bytecode

	// ------------------------- Operand class ------------------------- //

	operand::operand(const std::string& lexeme, std::uint8_t type, std::uint64_t value)
		: _lexeme(lexeme), _type(type), _value(value) {}

	operand::operand(std::string lexeme) {
		_lexeme = lexeme;
		_token	= lexeme;

		// Address (register/numerical)
		if (lexeme.front() == '[' && lexeme.back() == ']') {
			lexeme.pop_back();
			lexeme.erase(lexeme.begin());

			_type = ADDRESS;

			// Numerical address
			if (isdigit(lexeme.front())) {
				// Read 8 bytes from the address
				_value	 = x64::utils::read_bytes(_value, 8);
				_pointer = std::stoull(lexeme);
			}

			// Register address
			else {
				// Safeguard
				lexeme = x64::utils::to_lower(lexeme);

				_pointer = *(register_table.at(lexeme));
				_value	 = x64::utils::read_bytes(_pointer, 8);
			}
		} else if (lexeme.front() == 'r') {
			_type  = REGISTER;
			_value = *(register_table.at(lexeme));
		} else if (isdigit(lexeme.front())) {
			_type  = IMMEDIATE;
			_value = std::stoull(lexeme);
		} else {
			// Label
			_type	 = ADDRESS; // or should i use LABEL?
			_pointer = _value = labels.at(lexeme);
		}

		// probs redundant? idk
		used = true;
	}

} // namespace x64