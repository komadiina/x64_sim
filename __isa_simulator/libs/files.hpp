#ifndef _FILES_HPP
#define _FILES_HPP

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>

namespace x64::utils {
	std::vector<std::string> read_file(const std::string& filename);
} // namespace x64::utils

#endif // _FILES_HPP
