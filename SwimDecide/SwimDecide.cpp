// SwimDecide.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSVHelper.h"
#include "ValChecker.h"
#include <iostream>
#include <fstream>

//struct Swimmer {
//	std::string name;
//	std::
//};

std::string fileName = "c:\\users\\john\\desktop\\book1.csv";

int main(){
	std::ifstream fin(fileName);

	while (!fin) {
		std::cout << "Problem opening file.\n";
		std::cout << "Confirm file is in this location: " << fileName << "\n";
		system("pause");
	}
	std::string line;
	std::getline(fin, line);

	int rowNum = 1;
	while (!fin.eof()) {
		std::string line;
		std::getline(fin, line);
		//std::cout << line << "\n";
		std::deque<std::string> swimmerDets = CSVHelper::parseLine(line);
		std::string error_string = ValChecker::check(swimmerDets);
		if (error_string.size() > 0) {
			std::cout << "Row " << rowNum << ": " << error_string << "\n";
			std::cout << "Would you like to correct it? Y or N: \n";
			system("pause");
			continue;
		}
		int a = 0;
		/*for (std::deque<std::string>::iterator it = swimmerDets.begin(); it != swimmerDets.end(); ++it) {
			std::cout << a << ": " << *it << "\n";
			a++;
		}
		std::cout << '\n';
		std::cout << "Size of deque: " << swimmerDets.size() << "\n\n";*/
		rowNum++;
	}

	system("pause");
}


