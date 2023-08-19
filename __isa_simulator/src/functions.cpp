#include "../libs/functions.hpp"

namespace x64 {
	void setbit(uint16_t bitflag) { registers::flags |= bitflag; }
	void clearbit(uint16_t bitflag) { registers::flags &= ~bitflag; }

	void setflag(uint16_t flag) { registers::flags |= flag; }
	void toggleflag(uint16_t flag) { registers::flags ^= flag; }

	void add(uint64_t& dest, uint64_t src) { dest += src; }
	void sub(uint64_t& dest, uint64_t src) { dest -= src; }
	void mul(uint64_t& dest, uint64_t src) { dest *= src; }
	void div(uint64_t& dest, uint64_t src) { dest /= src; }

	// Assembly-type comparison using 'flags' register
	void cmp(uint64_t& dest, uint64_t src) {
		if (dest == src) {
			// Set the zero flag to 1, the carry flag to 0
			setbit(registers::ZF);
			clearbit(registers::CF);
		} else if (dest < src) {
			// Set the zero flag to 0, the carry flag to 1
			clearbit(registers::ZF);
			setbit(registers::CF);
		} else if (dest > src) {
			// Set the zero flag to 0, the carry flag to 0
			clearbit(registers::ZF);
			clearbit(registers::CF);
		}
	}

	void _and(uint64_t& dest, uint64_t src) { dest &= src; }
	void _or(uint64_t& dest, uint64_t src) { dest |= src; }
	void _xor(uint64_t& dest, uint64_t src) { dest ^= src; }
	void _not(uint64_t& dest) { dest = ~dest; }

	void move(uint64_t& dest, uint64_t src) { dest = src; }

	// Control flow
	void jmp(uint64_t& dest) { registers::rip = dest; }
	void je(uint64_t& dest) {
		if (registers::flags & registers::ZF && !(registers::flags & registers::CF))
			jmp(dest);
	}
	void jne(uint64_t& dest) {
		if (!(registers::flags & registers::ZF))
			jmp(dest);
	}
	void jg(uint64_t& dest) {
		if (!(registers::flags & registers::ZF) && !(registers::flags & registers::CF))
			jmp(dest);
	}
	void jge(uint64_t& dest) {
		if (!(registers::flags & registers::CF))
			jmp(dest);
	}
	void jl(uint64_t& dest) {
		if (registers::flags & registers::CF && !(registers::flags & registers::ZF))
			jmp(dest);
	}
	void jle(uint64_t& dest) {
		if (registers::flags & registers::ZF || registers::flags & registers::CF)
			jmp(dest);
	}
} // namespace x64