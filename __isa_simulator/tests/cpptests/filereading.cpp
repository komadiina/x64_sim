#include <iomanip>
#include <iostream>

#include "../../libs/encoding.hpp"
#include "../../libs/files.hpp"
#include "../../libs/functions.hpp"
#include "../../libs/lexer.hpp"
#include "../../libs/vars.hpp"

int main(int argC, char** argV) {
	assert(argC == 2);
	std::string fpath = argV[1];

	auto code = x64::utils::read_file(fpath);
	for (auto& line : code) {
		std::cout << line << std::endl;
	}

	return EXIT_SUCCESS;
}