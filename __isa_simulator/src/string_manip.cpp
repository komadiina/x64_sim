#include "../libs/string_manip.hpp"

namespace x64::utils {
	std::string to_lower(std::string str) {
#pragma omp parallel for
		{
			for (auto& c : str)
				c = std::tolower(c);
		}

		return str;
	}

	std::vector<std::string> tokenize(std::string& s) {
		// Trim surrounding whitespace
		boost::trim(s);

		// Tokenize via whitespace
		boost::char_separator<char> sep{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{s, sep};

		std::vector<std::string> tokens_vec{tokens.begin(), tokens.end()};

		// Tokenized string
		return tokens_vec;
	}

	std::vector<std::string> tokenize(const std::string& _s) {
		// Trim surrounding whitespace
		std::string s{_s};
		boost::trim(s);

		// Tokenize via whitespace
		boost::char_separator<char> sep{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{s, sep};

		std::vector<std::string> tokens_vec{tokens.begin(), tokens.end()};

		// Tokenized string
		return tokens_vec;
	}
} // namespace x64::utils