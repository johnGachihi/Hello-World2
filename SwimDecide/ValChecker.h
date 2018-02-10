#pragma once
#ifndef SWIMMER_H
#define SWIMMER_H

#include <deque>
#include <string>
#include <sstream>
#include <cctype>
#include <deque>

class ValChecker {
public:
	static std::string check(std::deque<std::string> tokens) {
		if (tokens.size() <= 7)
			return "Incomplete data collected";

		if (!isInteger(tokens[0]))
			return "Wrong type in column 1";

		if (tokens[1].empty())
			return "Swimmer Name not provided";

		if (!dateIsValid(tokens[2]))
			return "Invalid date of birth provided";

		if (!isInteger(tokens[3]))
			return "Wrong type in column four";

	}


private:
	static bool isInteger(std::string data) {
		for (int i = 0; i < data.size(); i++)
			if (!isdigit(data[i]))
				return false;
		return true;
	}

	static bool dateIsValid(std::string &s_date) {
		//Date format: DD/MM/YYYY
		std::string splitDate[3];
		int index = 0;
		for (int i = 0; i < s_date.size(); i++) {
			if (s_date[i] == ' ')
				s_date.erase(i, 1);
			else if (s_date[i] == '/') {
				if(++index > 2) return false;
			}
			else if (isdigit(s_date[i]))
				splitDate[index].append(1, s_date[i]);
			else
				return false;
		}
		if (s_date.size() != 10)
			return false;

		if (std::stoi(splitDate[0]) <= 31 &&
			std::stoi(splitDate[1]) <= 12 &&
			splitDate[2].size() == 4)
			return true;

		return false;
	}
};
#endif