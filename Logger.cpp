#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <utility>
#include <sstream>

std::ostream& args_to_stream(std::ostream &os)
{
	return os;
}

template <typename First, typename ...Args>
std::ostream& args_to_stream(std::ostream &os, First&& first, Args&& ...args) {
	os << std::forward<First>(first);
	return args_to_stream(os, std::forward<Args>(args)...);
}

template <typename ...Args>
std::string combine_to_string(Args&& ...args)
{
	std::ostringstream ss;
	args_to_stream(ss, std::forward<Args>(args)...);
	return ss.str();
}

template<class TLevel>
class Logger {
private:
	std::ostream &os_;
public:
	Logger(std::ostream &os) : os_(os) {}

	template<typename ...Args>
	std::string log_to_string(TLevel level, Args&& ...args) { return combine_to_string(level, std::forward<Args>(args)...); }

	template<typename ...Args>
	void log_to_stream(TLevel level, Args&& ...args) { args_to_stream(os_, level, std::forward<Args>(args)...); }
};

int main()
{
	Logger<std::string> logger(std::cout);

	logger.log_to_stream("Warning: ", "ip address ", "10.0.0.1 ", "port ", 5000, "\n");

	std::cout << logger.log_to_string("Exception: ", "Adress ", 0x123432, " not found", "\n");
}
 