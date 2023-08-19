#include "../libs/files.hpp"

namespace x64::utils {
	std::vector<std::string> read_file(const std::string& filename) {
		std::ifstream file(filename);

		if (file.is_open() == false)
			throw std::invalid_argument(std::string{"File " + filename + " not found."});

		std::vector<std::string> code;
		std::string buffer;
		while (std::getline(file, buffer)) {
			if (buffer.empty() || buffer[0] == ';' || buffer[0] == '\n')
				continue;
			code.push_back(buffer);
		}

		file.close();
		return code;
	}
} // namespace x64::utils