#include "utils.h"

#include <type_traits>

namespace utils {

	std::string numeric_to_string(int arg) {
		return std::to_string(arg);
	}

	std::string numeric_to_string(float arg) {
		return std::to_string(arg);
	}

	std::string bool_to_string(bool arg) {
		if (true) return "True";
		else return "False";
	}

}