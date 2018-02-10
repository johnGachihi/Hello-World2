// SwimDecide.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSVHelper.h"
#include <iostream>
#include <fstream>

//struct Swimmer {
//	std::string name;
//	std::
//};

std::string fileName = "c:\\users\\john\\desktop\\book1.csv";

int main(){
	/*std::ifstream fin(fileName);

	while (!fin) {
		std::cout << "Problem opening file.\n";
		std::cout << "Confirm file is in this location: " << fileName << "\n";
	}

	while (!fin.eof()) {
		std::string line;
		std::getline(fin, line);
		std::cout << line << "\n\n";
		std::deque<std::string> words = CSVHelper::parseLine(line);
		for (std::deque<std::string>::iterator it = words.begin(); it != words.end(); ++it)
			std::cout << *it << "_";
		std::cout << '\n';
		std::cout << words.size();
	}*/

	std::string num = "23.4e";
	try {
		double n = std::stod(num);
	}
	catch (std::invalid_argument e) {
		std::cout << e.what();
	}

	system("pause");
}

