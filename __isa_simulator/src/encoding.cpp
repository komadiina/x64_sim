#include "../libs/encoding.hpp"

namespace x64::bytecode {
	void initialize() {
		instruction_ids.clear();

		auto i = 0x01;
		for (auto& mnemonic : instruction_set)
			instruction_ids[mnemonic] = i++;

		is_initialized = true;
	}

	instruction get_instruction(std::string mnemonic) {
		// Initialize instruction opcodes
		if (is_initialized == false)
			initialize();

		// Remove comments
        auto range = boost::find_first(mnemonic, ";");
        if (!range.empty())
			mnemonic.erase(range.end(), mnemonic.end());

		// Lowercase, remove all commas and tokenize the mnemonic
		mnemonic = x64::utils::to_lower(mnemonic);
		boost::algorithm::erase_all(mnemonic, ",");
		auto tokens = x64::utils::tokenize(mnemonic);

		// Empty instruction is not allowed
		assert(tokens.size() > 0);

		instruction instr;
        instr.second = std::vector<x64::operand>();

		// Check if the instruction is a label
		if (tokens.at(0).back() == ':') {
			tokens.at(0).pop_back();

			labels[tokens.at(0)] = x64::registers::rip;
			instr.first			 = std::byte{LABEL};
			instr.second.front() = x64::operand(tokens.at(0), LABEL, x64::registers::rip); // was [0] instead of front()

			return instr;
		}

		// Invalid instruction
		if (instruction_set.count(tokens[0]) == 0)
			throw std::runtime_error("Invalid instruction: " + tokens[0]);

		// Get the instruction
		instr.first ^= std::byte{0x00};
		instr.first ^= std::byte{instruction_ids.at(tokens[0])};
		tokens.erase(tokens.begin());

		// Append tokens to operand vector
		for (auto token : tokens)
			instr.second.push_back(token);

		return instr;
	}

	std::vector<std::byte> encode(const instruction& instr) {
		uint8_t hex_shift = 4;
		std::vector<std::byte> bytecode;

		// Each instr. ID expects N operands, so that's one way of telling it
		bytecode.push_back(instr.first);

		uint8_t i = 0;
		for (; i < instr.second.size(); i++) {
			bytecode.push_back(std::byte{instr.second[i].type()});
		}

		for (uint8_t j = 0; j < i; j++) {
			// Get the byte-vector of the operand
			x64::bytes bytes = x64::utils::to_bytes(instr.second[j].value());

			// Reverse from big endian to little endian
			std::reverse(bytes.begin(), bytes.end());

			// Append the operand to the bytecode vector
			bytecode.insert(bytecode.begin() + bytecode.size(), bytes.begin(), bytes.end());
		}

		return bytecode;
	}

	uint64_t write_bytecode(std::vector<std::byte> bytecode, uint64_t& address) {
		for (auto byte : bytecode)
			x64::memory[address++] = byte;

		return address++;
	}
} // namespace x64::bytecode