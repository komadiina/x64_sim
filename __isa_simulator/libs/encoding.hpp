#pragma once

#include "./functions.hpp"
#include "./string_manip.hpp"
#include "./vars.hpp"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iostream>


namespace x64::bytecode {
	void initialize();

	std::vector<std::byte> encode(const instruction&);
	std::vector<std::uint8_t> encode_uint(const instruction&);
	uint64_t write_bytecode(std::vector<std::byte> bytecode, uint64_t& address);
	instruction get_instruction(std::string);
} // namespace x64::bytecode