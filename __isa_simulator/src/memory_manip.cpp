#include "../libs/memory_manip.hpp"

namespace x64::utils {
	uint64_t read_bytes(uint64_t address, uint8_t num_bytes = 8) {
		std::vector<std::byte> byte_vector;
		for (std::size_t ip = 0; ip < num_bytes; ++ip)
			byte_vector.insert(byte_vector.begin(), x64::memory[address + ip * 0x01]);

		uint64_t value = 0LL;
		for (std::size_t i = 0; i < sizeof(value); ++i)
			value |= static_cast<uint64_t>(byte_vector[i]) << (i * 8);

		return value;
	}

	std::vector<std::byte> to_bytes(uint64_t value) {
		std::vector<std::byte> byte_vector;
		for (std::size_t i = 0; i < sizeof(value); ++i)
			byte_vector.insert(byte_vector.begin(),
							   std::byte{static_cast<uint8_t>(value >> (i * 8))});
		return byte_vector;
	}

	uint64_t write_bytes(uint64_t address, uint64_t value, uint8_t num_bytes) {
		std::vector<std::byte> byte_vector = to_bytes(value);

		for (std::size_t ip = 0; ip < num_bytes; ++ip)
			x64::memory[address + ip * 0x01] = byte_vector[ip];

		return address + num_bytes + 0x01;
	}

} // namespace x64::utils