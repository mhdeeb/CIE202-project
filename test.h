//
// Created by Mohamed Hussien El-Deeb on 12/20/2022.
//

#ifndef CIE_202_TEST_H
#define CIE_202_TEST_H

#include <iostream>

namespace test {
	std::string _sep = " ";
	std::string _end = "\n";

	void print() { std::cout << _end; }

	template<typename T, typename ...Args>
	void print(const T& t, Args &&... args) {
		std::cout << t << _sep;
		print(args...);
	}

	void sep(std::string_view separator) {
		_sep = separator;
	}

	void end(std::string_view ending) {
		_end = ending;
	}
}

#endif //CIE_202_TEST_H
