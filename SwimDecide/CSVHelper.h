#pragma once
#ifndef CSVHELPER_H
#define CSVHELPER_H

#include <deque>
#include <string>
#include <sstream>

class CSVHelper {
public:
	static std::deque<std::string> parseLine(std::string line) {
		std::deque<std::string> words;
		std::stringstream ss;
		bool started = false;
		bool inQuotes = false;
		for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
			if (inQuotes) {
				started = true;
				if (*it == '\"')
					inQuotes = false;
				else
					ss << *it;
			}
			else {
				if (*it == '\"') {
					inQuotes = true;
					if (started)
						ss << *it;
				}
				else if (*it == ',') {
					words.push_back(ss.str());
					ss.str("");
				}
				else if (*it == '\n')
					break;
				else if (*it == '\r') {

				}
				else
					ss << *it;
			}
		}
		words.push_back(ss.str());
		return words;
	}
};

#endif