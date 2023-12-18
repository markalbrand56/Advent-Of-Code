#include <iostream>
#include "reader.h"

using namespace std;

void part_1(){
	cout << "Part 1" << endl;

	Reader reader("sample.txt");

	vector<string> contents = reader.getContents();

	for (string line : contents) {
		cout << line << endl;
	}
}