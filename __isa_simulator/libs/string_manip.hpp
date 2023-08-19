#ifndef _STRING_MANIP_HPP
#define _STRING_MANIP_HPP

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include <omp.h>

namespace x64::utils {
	std::string to_lower(std::string str);
	std::vector<std::string> tokenize(std::string& s);
	std::vector<std::string> tokenize(const std::string& _s);
} // namespace x64::utils

#endif // _STRING_MANIP_HPP