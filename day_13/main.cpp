#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void part_1(const string& filename);
void part_2(const string& filename);

int main() {
	std::cout << "Hello, World!" << std::endl;

	part_1("input.txt");
	part_2("input.txt");

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

int diff_in_pattern(string s1, string s2){
	int diff = 0;
	for(int i = 0; i < s1.length(); i++){
		if (s1[i] != s2[i]){
			diff++;
		}
	}

	return diff;
}

int hr(vector<string> pattern){
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

	return horizontal_reflection;
}

int vr(vector<string> pattern){
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

	return vertical_reflection;
}

int lf_hr(vector<string> pattern, int original_hr){
	int horizontal_reflection = -1;
	for (int i = 1; i < pattern.size(); ++i){
		string current_line = pattern[i];
		string prev_line = pattern[i-1];

		if(current_line == prev_line){
			bool reflection = true;
			// Verificar que se cumpla el reflejo
			auto k = i - 1;
			int differences = 0;
			for (int j = i; j < pattern.size() && k >= 0; j++){
				string c = pattern[j];
				string p = pattern[k];
				int d = diff_in_pattern(c,p);
				if(c != p){
					if(differences > 1){
						reflection = false;
					}else if (d == 1){
						differences++;
					}
				}
				k--;
			}

			if(reflection && original_hr != i){
				horizontal_reflection = i;
				break;
			}

		} else if (diff_in_pattern(current_line, prev_line) == 1){
			bool reflection = true;
			// Verificar que se cumpla el reflejo modificando un solo caracter en dos lineas que no son iguales
			auto k = i - 2;
			int differences = 0;
			for (int j = i+1; j < pattern.size() && k >= 0; j++){
				string c = pattern[j];
				string p = pattern[k];
				int d = diff_in_pattern(c,p);
				if(c != p){
					if(differences > 1){
						reflection = false;
					}else if (d > 1){
						reflection = false;
						break;
					}else if (d==1){
						differences++;
					}
				}
				k--;
			}

			if(reflection){
				horizontal_reflection = i;
				break;
			}
		}
	}

	return horizontal_reflection;
}

int lf_vr(vector<string> pattern, int original_vr){
	int vertical_reflection = -1;

	vector<string> pattern_tr;

	for (int j = 0; j < pattern[0].length() ; j++){
		string t = "";
		for(int i = 0; i < pattern.size(); i++){
			t += pattern[i][j];
		}
		pattern_tr.push_back(t);
	}

	for (int i = 1; i < pattern_tr.size(); ++i){
		string current_line = pattern_tr[i];
		string prev_line = pattern_tr[i-1];

		if(current_line == prev_line){
			bool reflection = true;
			// Verificar que se cumpla el reflejo
			auto k = i - 1;
			int differences = 0;
			for (int j = i; j < pattern_tr.size() && k >= 0; j++){
				string c = pattern_tr[j];
				string p = pattern_tr[k];
				int d = diff_in_pattern(c,p);
				if(c != p){
					if(differences > 1){
						reflection = false;
					}else if (d == 1){
						differences++;
					}
				}
				k--;
			}

			if(reflection && original_vr != i){
				vertical_reflection = i;
				break;
			}

		} else if (diff_in_pattern(current_line, prev_line) == 1){
			bool reflection = true;
			// Verificar que se cumpla el reflejo modificando un solo caracter en dos lineas que no son iguales
			auto k = i - 2;
			int differences = 0;
			for (int j = i+1; j < pattern_tr.size() && k >= 0; j++){
				string c = pattern_tr[j];
				string p = pattern_tr[k];
				int d = diff_in_pattern(c,p);
				if(c != p){
					if(differences > 1){
						reflection = false;
					}else if (d == 1){
						differences++;
					}
				}
				k--;
			}

			if(reflection){
				vertical_reflection = i;
				break;
			}
		}
	}

	return vertical_reflection;
}

void part_2(const string& filename){
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

		int original_hr = hr(pattern);
		int original_vr = vr(pattern);

		/* HORIZONTAL REFLECTION */
		int new_hr = lf_hr(pattern, original_hr);

		/* VERTICAL REFLECTION */
		int new_vr = lf_vr(pattern, original_vr);


		if(new_hr > 0){
			result += 100 * new_hr;
			cout << "\t" << 100 * new_hr << endl;
			continue;
		}

		if(new_vr > 0){
			result += new_vr;
			cout << "\t" << new_vr << endl;
			continue;
		}

		if (original_hr > 0){
			result += 100 * original_hr;
			cout << "\t" << 100 * original_hr << endl;
			continue;
		}
		if(original_vr > 0){
			result += original_vr;
			cout << "\t" << original_vr << endl;
			continue;
		}

	}

	cout << "Result: " << result << endl;
}