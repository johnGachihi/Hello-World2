// SwimDecide.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSVHelper.h"
#include "ValChecker.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>

#define CORRECT_ERROR 'C'
#define SKIP_ERROR 'S'
#define INPUT_IS_INVALID true

struct Swimmer {
	std::string No;
	std::string name;
	std::string dob;
	std::string heat;
	std::string distance;
	std::string time;
	std::string status;

	Swimmer(std::string No, std::string name, std::string dob,
		std::string heat, std::string distance, std::string time, std::string status)
	: No(No), name(name), dob(dob), heat(heat), distance(distance), time(time),
		status(status){}
};

typedef std::map<int, std::deque<Swimmer>> SwimmersMap;

std::ifstream openFile(std::string);
void handleError(int&, std::ifstream&);
void enableUserToHandleError(std::ifstream&, int&);
void printFromSwimmersMap(SwimmersMap&);
Swimmer createSwimmer(std::deque<std::string>);
bool sortAlgo(Swimmer, Swimmer);
void sortSwimmersByTime(SwimmersMap&);
int getSizeOfLongestName(std::deque<Swimmer>);
void formatPrint(Swimmer, int);
void formatPrint(std::deque<std::string>, int);

std::string fileName = "c:\\users\\john\\desktop\\book1.csv";
SwimmersMap swimmers_map;

int main(){
	/*std::ifstream csvfile(fileName, std::ios::binary);

	while (!csvfile) {
		std::cout << "Problem opening file.\n";
		std::cout << "Confirm file is in this location: " << fileName << "\n";
		system("pause");
		csvfile.open(fileName, std::ios::binary);
		system("cls");
	}*/
	std::ifstream csvfile = openFile(fileName);

	std::string line;
	std::getline(csvfile, line);

	int startOfCurrentLine = 0;
	int rowNum = 1;

	while (!csvfile.eof()) {
		startOfCurrentLine = csvfile.tellg();

		std::string line;
		std::getline(csvfile, line);
		std::cout << line << "\n";

		std::deque<std::string> swimmerDetails = CSVHelper::parseLine(line);
		std::string error_message = ValidityChecker::check(swimmerDetails);

		if (error_message.size() > 0) {
			system("cls");
			std::cout << "Error in Row " << rowNum << ": " << error_message << "\n";
			std::cout << line << "\n";

			handleError(startOfCurrentLine, csvfile);
			continue;
		}

		Swimmer swimmer = createSwimmer(swimmerDetails);
		swimmers_map[stoi(swimmer.distance)].push_back(createSwimmer(swimmerDetails));

		/*int a = 0;
		for (std::deque<std::string>::iterator it = swimmerDets.begin(); it != swimmerDets.end(); ++it) {
			std::cout << a << ": " << *it << "\n";
			a++;
		}
		std::cout << '\n';
		std::cout << "Size of deque: " << swimmerDets.size() << "\n\n";*/
		rowNum++;
	}

	sortSwimmersByTime(swimmers_map);

	printFromSwimmersMap(swimmers_map);

	system("pause");
}

std::ifstream openFile(std::string fileName) {
	std::ifstream csvfile(fileName, std::ios::binary);

	while (!csvfile) {
		std::cout << "Problem opening file.\n";
		std::cout << "Confirm file is in this location: " << fileName << "\n";
		system("pause");
		openFile(fileName);
		system("cls");
	}
	return csvfile;
}

void handleError(int& startOfErroneousLine, std::ifstream& file) {
	std::cout << "Would you like to Correct(C) or Skip(S) it?: ";
	char choice;
	while (INPUT_IS_INVALID) {
		std::cin >> choice;
		choice = tolower(choice);
		if (choice == 'c') {
			enableUserToHandleError(file, startOfErroneousLine);
			break;
		}
		else if (choice == 's')
			break;
		else {
			std::cout << "Invalid input\n";
			continue;
		}
	}
}

void enableUserToHandleError(std::ifstream& file, int& startOfCurrentLine) {
	//file.seekg(startOfCurrentLine);
	std::cout << "Opening file in excel .....\nRemember to save\n";
	std::string cmdCommandToOpenFile = "start excel " + fileName;
	system(cmdCommandToOpenFile.c_str());
	system("pause");
	file.close();
	file.open(fileName, std::ios::binary);
	file.seekg(startOfCurrentLine);
}

Swimmer createSwimmer(std::deque<std::string> swimmerDets) {
	Swimmer swimmer(swimmerDets[SWIMMER_NO], swimmerDets[SWIMMER_NAME],
		swimmerDets[SWIMMER_DOB], swimmerDets[SWIMMER_HEAT],
		swimmerDets[SWIMMER_DISTANCE], swimmerDets[SWIMMER_TIME],
		swimmerDets[SWIMMER_STATUS]);
	return swimmer;
}

void sortSwimmersByTime(SwimmersMap& swimmers_map) {
	for (SwimmersMap::iterator it = swimmers_map.begin(); it != swimmers_map.end(); it++) {
		std::cout << "Sorting: " << it->first << std::endl;
		std::sort((it->second).begin(), (it->second).end(), sortAlgo);
	}
}

bool sortAlgo(Swimmer swimmerA, Swimmer swimmerB) {
	if (swimmerA.status != "Q" && swimmerB.status == "Q")
		return false;
	if (swimmerA.status == "Q" && swimmerB.status != "Q")
		return true;
	return swimmerA.time < swimmerB.time;
}

void printFromSwimmersMap(SwimmersMap& sw) {
	for (SwimmersMap::iterator it = sw.begin(); it != sw.end(); it++) {
		std::cout << it->first << "M race results\n";
		int sizeOfLongestName = getSizeOfLongestName(it->second);
		Swimmer titles = createSwimmer({ "No", "Name", "DOB", "Heat", "Distance", "Time", "Status" });
		formatPrint(titles, sizeOfLongestName);
		/*std::deque<Swimmer> swimDets = it->second;
		for (std::deque<Swimmer>::iterator itt = 
			swimDets.begin(); itt != swimDets.end(); itt++) {
			Swimmer swimmer = *itt;
			std::cout << swimmer.name << " " << swimmer.distance
				<< " " << swimmer.time << " " << swimmer.status << std::endl;
			
		}*/
		for (Swimmer swimmer : it->second) {
			formatPrint(swimmer, sizeOfLongestName);
		}
		std::cout << std::endl;
	}
}

int getSizeOfLongestName(std::deque<Swimmer> swimmers) {
	Swimmer s = *std::max_element(swimmers.begin(), swimmers.end(),
		[&](Swimmer swimmerA, Swimmer swimmerB) -> bool
			{ return swimmerA.name.size() < swimmerB.name.size(); });
	return s.name.size();
}

void formatPrint(Swimmer swimmer, int sizeOfLongestName) {
	std::cout << std::left << std::setw(10) << swimmer.No;
	std::cout << std::left << std::setw(sizeOfLongestName + 8) << swimmer.name;
	std::cout << std::left << std::setw(15) << swimmer.dob;
	std::cout << std::left << std::setw(8) << swimmer.heat;
	std::cout << std::left << std::setw(10) << swimmer.distance;
	std::cout << std::left << std::setw(10) << swimmer.time;
	std::cout << std::left << std::setw(5) << swimmer.status << "\n";
}
