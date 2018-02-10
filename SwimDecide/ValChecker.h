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
	static bool check(std::deque<std::string> tokens) {
		if (tokens.size() <= 7)
			return false;
		if (isdigit(tokens[0].at(0)))
			return false;
		if (tokens[1].empty())
			return false;
		if (dateIsValid(tokens[2]))
			return false;

	}

private:
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
			splitDate[2].size == 4)
			return true;

		return false;
	}

};
#endif