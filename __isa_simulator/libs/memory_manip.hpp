#pragma once

#include "./vars.hpp"

namespace x64::utils {
	uint64_t read_bytes(uint64_t address, uint8_t num_bytes);
	std::vector<std::byte> to_bytes(uint64_t value);
	uint64_t write_bytes(uint64_t address, uint64_t value, uint8_t num_bytes );
} // namespace x64::utils