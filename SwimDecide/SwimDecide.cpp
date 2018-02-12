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
	std::ifstream file(fileName, std::ios::binary);

	while (!file) {
		std::cout << "Problem opening file.\n";
		std::cout << "Confirm file is in this location: " << fileName << "\n";
		system("pause");
		file.open(fileName, std::ios::binary);
		system("cls");
	}
	std::string line;
	std::getline(file, line);

	int startOfCurrentLine = 0;

	int rowNum = 1;
	while (!file.eof()) {
		startOfCurrentLine = file.tellg();

		std::string line;
		std::getline(file, line);

		std::deque<std::string> swimmerDetails = CSVHelper::parseLine(line);
		std::string error_message = ValidityChecker::check(swimmerDetails);

		
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

bool handleError(std::string error_message, int rownumber) {
	if (error_message.size() > 0) {
		std::cout << "Row " << rownumber << ": " << error_message << "\n";
		std::cout << "Would you like to Correct(C) or Skip(S) it?: ";
		char choice;
		while (true) {
			std::cin >> choice;
			if (choice == 'C') {

			}
		}
	}
}

void moveBackToStartOfLine() {

}


