#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Reader {
public:
	Reader(const string& filename); // Constructor

	vector<string> getContents(); // Getter

private:
	string filename;
	vector<string> contents;

};

Reader::Reader(const string& filename) {
	this->filename = filename;

	ifstream file(filename);

	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			contents.push_back(line);
		}

		file.close();
	}
}

vector<string> Reader::getContents() {
	return contents;
}


