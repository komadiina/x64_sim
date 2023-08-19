#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include "./vars.hpp"

namespace x64 {
	// Arithmetics
	void add(uint64_t& dest, uint64_t src);
	void sub(uint64_t& dest, uint64_t src);
	void mul(uint64_t& dest, uint64_t src);
	void div(uint64_t& dest, uint64_t src);

	// Logicals
	void cmp(uint64_t& dest, uint64_t src);
	void _and(uint64_t& dest, uint64_t src);
	void _or(uint64_t& dest, uint64_t src);
	void _xor(uint64_t& dest, uint64_t src);
	void _not(uint64_t& dest);

	// Memory manipulation
	void move(uint64_t& dest, uint64_t src);

	// Control flow
	void jmp(uint64_t& dest);
	void je(uint64_t& dest);
	void jne(uint64_t& dest);
	void jg(uint64_t& dest);
	void jge(uint64_t& dest);
	void jl(uint64_t& dest);
	void jle(uint64_t& dest);

	// Flags (for setting conditionals)
	void setflag(uint16_t flag);
	void toggleflag(uint16_t flag);

	void setbit(uint16_t bitflag);
	void clearbit(uint16_t bitflag);

} // namespace x64