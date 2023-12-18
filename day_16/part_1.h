#include <iostream>
#include "reader.h"

using namespace std;

enum Direction {
	RIGHT = 1,
	LEFT = -1,
	UP = 2,
	DOWN = -2
};

struct Beam {
	int x;
	int y;
	Direction direction;
	bool active = true;
};

void part_1(){
	cout << "Part 1" << endl;

	Reader reader("input.txt");

	vector<string> map = reader.getContents();
	vector<string> result = map;

	// replace every '\' '/' '-' '|' with '.' in result
	for (int i = 0; i < result.size(); i++) {
		string line = result[i];
		for (int j = 0; j < line.size(); j++) {
			char c = line[j];
			if (c == '\\' || c == '/' || c == '-' || c == '|') {
				result[i][j] = '.';
			}
		}
	}

	for (string line : map) {
		cout << line << endl;
	}

	/*

	 Directions:
	 	Right
	 	Left
	 	Up
	 	Down

	 Redirections:
	 	/ + (Right -> Up
	 	/ + (Left) -> Down
	 	/ + (Up) -> Right
	 	/ + (Down) -> Left

	 	\ + (Right) -> Down
	 	\ + (Left) -> Up
	 	\ + (Up) -> Left
	 	\ + (Down) -> Right

	Splitters:
	 	| + (Right or left) -> Up and Down
	 	- + (Up or Down) -> Right and Left
	 	| + (Up or Down) -> Goes through
	 	- + (Right or Left) -> Goes trough

	Start: Beam on 0,0 going right

	Wherever a beam pases, it becomes energized ('.' -> '#')
	The beams will continue until they hit a splitter or a corner

	 */

	vector<Beam> beams;
	int activeBeams = 1;
	beams.push_back({ 0, 0, RIGHT });

	while (activeBeams > 0){
		for (int i = 0; i < beams.size(); i++) {
			Beam beam = beams[i];

			if (beam.x < 0 || beam.x >= map[0].size() || beam.y < 0 || beam.y >= map.size()) {
				// Beam is out of bounds
				beams[i].active = false;
				activeBeams--;
				continue;
			}

			char cell = map[beam.y][beam.x];

			for (int j = 0; j < beams.size(); j++) {
				Beam b = beams[j];
				if (beam.x == b.x && beam.y == b.y && beam.direction == b.direction && i != j) {
					// There is a beam in the same position and direction that passed before
					beams[i].active = false;
					break;
				}
			}

			if (!beams[i].active) {
				continue;
			}

			switch (beam.direction) {
				case RIGHT:
					if (cell == '/') {
						beams.push_back({ beam.x, beam.y - 1, UP }); // Current beam goes up
					}
					else if (cell == '\\') {
						beams.push_back({ beam.x, beam.y + 1, DOWN }); // Current beam goes down
					}
					else if (cell == '|') {
						// Splits
						beams.push_back({ beam.x, beam.y + 1, DOWN }); // Current beam goes down
						beams.push_back({ beam.x, beam.y - 1, UP }); // Current beam goes up
						activeBeams++;
					}
					else if (cell == '-') {
						// Keeps going right
						beams.push_back({ beam.x + 1, beam.y, RIGHT });
					}
					else {
						// Keeps going right
						beams.push_back({ beam.x + 1, beam.y, RIGHT });
					}

					beams[i].active = false;

					break;
				case LEFT:
					if (cell == '/') {
						beams.push_back({ beam.x, beam.y + 1, DOWN }); // Current beam goes down
					}
					else if (cell == '\\') {
						beams.push_back({ beam.x, beam.y - 1, UP }); // Current beam goes up
					}
					else if (cell == '|') {
						// Splits
						beams.push_back({ beam.x, beam.y + 1, DOWN }); // Current beam goes down
						beams.push_back({ beam.x, beam.y - 1, UP }); // Current beam goes up
						activeBeams++;
					}
					else if (cell == '-') {
						// Keeps going left
						beams.push_back({ beam.x - 1, beam.y, LEFT });
					}
					else {
						// Keeps going left
						beams.push_back({ beam.x - 1, beam.y, LEFT });
					}

					beams[i].active = false;

					break;
				case UP:
					if (cell == '/') {
						beams.push_back({ beam.x + 1, beam.y, RIGHT }); // Current beam goes right
					}
					else if (cell == '\\') {
						beams.push_back({ beam.x - 1, beam.y, LEFT }); // Current beam goes left
					}
					else if (cell == '|') {
						beams.push_back({ beam.x, beam.y - 1, UP }); // Keeps going up
					}
					else if (cell == '-') {
						// Splits
						beams.push_back({ beam.x + 1, beam.y, RIGHT }); // Current beam goes Right
						beams.push_back({ beam.x - 1, beam.y, LEFT }); // Current beam goes Left
					}
					else{
						// Keeps going up
						beams.push_back({ beam.x, beam.y - 1, UP });
					}

					beams[i].active = false;
					break;
				case DOWN:
					if (cell == '/') {
						beams.push_back({ beam.x - 1, beam.y, LEFT }); // Current beam goes left
					}
					else if (cell == '\\') {
						beams.push_back({ beam.x + 1, beam.y, RIGHT }); // Current beam goes right
					}
					else if (cell == '|') {
						beams.push_back({ beam.x, beam.y + 1, DOWN }); // Keeps going down
					}
					else if (cell == '-') {
						// Splits
						beams.push_back({ beam.x + 1, beam.y, RIGHT }); // Current beam goes Right
						beams.push_back({ beam.x - 1, beam.y, LEFT }); // Current beam goes Left
					}
					else {
						// Keeps going down
						beams.push_back({ beam.x, beam.y + 1, DOWN });
					}

					beams[i].active = false;

					break;
			}
			result[beam.y][beam.x] = '#';
		}
	}

	cout << "Result" << endl;
	for (string line : result) {
		cout << line << endl;
	}

	// count '#' in result
	int count = 0;
	for (string line : result) {
		for (char c : line) {
			if (c == '#') {
				count++;
			}
		}
	}

	cout << "Result: " << count << endl;

}