#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

struct Employee {
	string name;
	int birthYear;
};

const int Max_em = 1000;

int getCurrentYear() {
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);
	return now.tm_year + 1900;
}


int correctYear(int birthYear) {
	if (birthYear > 1000) return birthYear;
	return (birthYear > getCurrentYear() % 100) ? (1900 + birthYear) : (2000 + birthYear);
}

void intersectionSort(Employee employ[], int n) {
	for (int i = 1; i < n; i++) {
		Employee key = employ[i];
		int j = i - 1;
		while (j >= 0 && (employ[j].birthYear < key.birthYear || (employ[j].birthYear == key.birthYear && employ[j].name > key.name))) {
			employ[j + 1] = employ[j];
			j--;
		}
		employ[j + 1] = key;
	}
}


void selectionSort(Employee employ[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int maxIn = i;
		for (int j = i + 1; j < n; j++) {
			if (employ[j].birthYear > employ[maxIn].birthYear ||
				(employ[j].birthYear == employ[maxIn].birthYear && employ[j].name < employ[maxIn].name)) {
				maxIn = j;
			}
		}
		swap(employ[i], employ[maxIn]);
	}
}

void interchangeSort(Employee employees[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (employees[j].birthYear > employees[i].birthYear ||
				(employees[j].birthYear == employees[i].birthYear && employees[j].name < employees[i].name)) {
				swap(employees[i], employees[j]);
			}
		}
	}
}

void writeToFile(Employee employees[], int n) {
	ofstream outFile("sortedemponage.txt");
	for (int i = 0; i < n; i++) {
		outFile << employees[i].name << " " << employees[i].birthYear << endl;
	}
	outFile.close();
}

int main() {
	ifstream inFile("employee.txt");
	Employee employees[Max_em];
	int count = 0;
	string line;

	while (getline(inFile, line) && count < Max_em) {
		stringstream ss(line);
		string name;
		int birthYear;
		ss >> name >> birthYear;
		birthYear = correctYear(birthYear);
		employees[count++] = { name, birthYear };
	}
	inFile.close();

	int choice;
	cout << "Select sorting algorithm:\n1. Insertion Sort\n2. Selection Sort\n3. Interchange Sort\nChoice: ";
	cin >> choice;

	switch (choice) {
	case 1: intersectionSort(employees, count); break;
	case 2: selectionSort(employees, count); break;
	case 3: interchangeSort(employees, count); break;
	default: cout << "Invalid choice!"; return 1;
	}

	writeToFile(employees, count);
	cout << "Sorting complete. Check sortedemponage.txt" << endl;
	return 0;
}