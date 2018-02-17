#pragma once
#ifndef SWIMMER_H
#define SWIMMER_H

#include <string>
#include <sstream>
#include <cctype>
#include <deque>
#include <iostream>

#define SWIMMER_NO 0
#define SWIMMER_NAME 1
#define SWIMMER_DOB 2
#define SWIMMER_HEAT 3
#define SWIMMER_DISTANCE 4
#define SWIMMER_TIME 5
#define SWIMMER_STATUS 6

#define NO_OF_COLUMNS 7

#define DAYS_IN_MONTH 31
#define MONTHS_IN_YEAR 12
#define DAY 0
#define MONTH 1
#define YEAR 2

class ValidityChecker {
public:
	static std::string check(std::deque<std::string> swimmerDets) {
		if (swimmerDets.size() < NO_OF_COLUMNS)
			return "Incomplete data collected";

		if (!isInteger(swimmerDets[SWIMMER_NO]))
			return "Wrong type in the No column";

		if (swimmerDets[SWIMMER_NAME].empty())
			return "Swimmer Name not provided";

		if (!dateIsValid(swimmerDets[SWIMMER_DOB]))
			return "Invalid date of birth provided";

		if (!isInteger(swimmerDets[SWIMMER_HEAT]))
			return "Wrong type in column four";

		if (!distanceIsValid(swimmerDets[SWIMMER_DISTANCE]))
			return "Distance is in wrong format";

		if (!timeIsValid(swimmerDets[SWIMMER_TIME]))
			return "Error in time column";

		std::string status = swimmerDets[SWIMMER_STATUS];
		if (status != "" && status != "Q" &&
			status != "DNF" && status != "DQ")
			return "Error in status column. Input here can only be '-', 'Q','DNF', 'DQ'\nGiven: " + status;

		if (swimmerDets[SWIMMER_TIME].empty() &&
			swimmerDets[SWIMMER_STATUS] != "DNF")
			return "Time not provided!";

		return "";
	}


	static bool timeIsValid(std::string time) {
		if (time.empty()) return true;

		std::stringstream ss(time);
		double _time;
		ss >> _time;
		return !ss ? false : true;
	}

	static bool distanceIsValid(std::string distance) {
		std::stringstream ss(distance);
		int dist;
		std::string unit;
		ss >> dist >> unit;

		if (!ss || (unit != "m" && unit != "M"))
			return false;

		return true;
	}

	static bool isInteger(std::string data, int start, int range) {
		for (int i = start; i < range; i++)
			if (!isdigit(data[i]))
				return false;
		return true;
	}

	static bool isInteger(std::string data) {
		if (data.size() <= 0)
			return false;

		for (int i = 0; i < data.size(); i++)
			if (!isdigit(data[i]))
				return false;
		return true;
	}

	static bool dateIsValid(std::string& date) {
		//Date format: 'DD/MM/YYYY'
		std::string splitDate[3];
		int index = 0;

		std::size_t a = date.find(" ");
		while (a != std::string::npos) {
			date.erase(a, 1);
			a = date.find(" ");
		}

		for (int i = 0; i < date.size(); i++) {
			if (date[i] == '/') {
				if (++index > 2) {
					std::cout << "More than three sections\n";
					return false;
				}
			}
			else if (isdigit(date[i]))
				splitDate[index].append(1, date[i]);
			else {
				std::cout << "Non-digit in date data\n";
				return false;
			}
		}
		if (date.size() != 10) {
			std::cout << "Date size is not equal to 10:" << date << "\n";
			return false;
		}

		if (std::stoi(splitDate[DAY]) <= DAYS_IN_MONTH &&
			std::stoi(splitDate[MONTH]) <= MONTHS_IN_YEAR &&
			splitDate[YEAR].size() == 4)
			return true;

		return false;
	}
};
#endif