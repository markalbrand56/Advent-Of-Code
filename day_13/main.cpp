#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void part_1(const string& filename);

int main() {
	std::cout << "Hello, World!" << std::endl;

	part_1("input.txt");

	return 0;
}

void part_1(const string& filename){
	ifstream file(filename);

	if (!file.is_open()){
		cout << "File not found" << endl;
		return;
	}

	string line;
	vector<vector<string>> patterns;
	vector<string> input_pattern;
	while (getline(file, line)){
		if(line.empty()){
			patterns.push_back(input_pattern);
			input_pattern.clear();
		}
		else{
			input_pattern.push_back(line);
		}
	}
	patterns.push_back(input_pattern);

	long long result = 0;

	for (int index = 0; index < patterns.size(); index++ ){
		auto pattern = patterns[index];
		/* HORIZONTAL REFLECTION */
		int horizontal_reflection = -1;
		for (int i = 1; i < pattern.size(); ++i){
			string current_line = pattern[i];
			string prev_line = pattern[i-1];

			if(current_line == prev_line){
				bool reflection = true;
				// Verificar que se cumpla el reflejo
				auto k = i - 1;
				for (int j = i; j < pattern.size() && k >= 0; j++){
					string c = pattern[j];
					string p = pattern[k];
					if(c != p){
						reflection = false;
					}
					k--;
				}

				if(reflection){
					horizontal_reflection = i;
				}

			}
		}
		if(horizontal_reflection > 0){
//			cout << "Horizontal on " << index << endl;
			result += 100 * horizontal_reflection;
			cout << "\t" << 100 * horizontal_reflection << endl;
			continue;
		}

		/* VERTICAL REFLECTION */
		int vertical_reflection = -1;
		int j = 1; // Columna
		auto l = pattern[j].length();

		for (; j < l; j++){
			bool reflection = true;
			for(int i = 0; i < pattern.size(); i++){
				char current = pattern[i][j];
				char previous = pattern[i][j-1];

				if(current != previous){
					reflection = false;
					break; // Next column
				}
			}

			if (reflection){
				int m = j;
				int n = j-1;
				bool clasifies = true;

				while(m < l && n >= 0){
					for(int i = 0 ;i < pattern.size(); i++){
						char c = pattern[i][m];
						char p = pattern[i][n];

						if(c != p){
							clasifies = false;
						}
					}
					m++;
					n--;
				}

				if (clasifies){
					vertical_reflection = j;
					break;
				}
			}
		}

		if (vertical_reflection > 0){
			result += vertical_reflection;
			cout << "\t" << vertical_reflection << endl;
		}

	}

	cout << "Result: " << result << endl;
}
