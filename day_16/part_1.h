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

	char startChar = map[0][0];

	if (startChar == '/') {
		beams.push_back({ 0, 0, UP });
	}
	else if (startChar == '\\') {
		beams.push_back({ 0, 0, DOWN });
	}
	else if (startChar == '|') {
		beams.push_back({ 0, 0, UP });
		beams.push_back({ 0, 0, DOWN });
		activeBeams++;
	}
	else if (startChar == '-') {
		beams.push_back({ 0, 0, RIGHT });
	}
	else {
		beams.push_back({ 0, 0, RIGHT });
	}

	result[0][0] = '#';

	while (activeBeams > 0){
		for (int i = 0; i < beams.size(); i++) {
			Beam beam = beams[i];
			char next;

			if (!beam.active) {
				continue;
			}

			switch (beam.direction) {
				case RIGHT:
					if (beam.x + 1 >= map[beam.y].size()) {
						activeBeams--;
						beams[i].active = false;
						break;
					}

					next = map[beam.y][beam.x + 1];

					if (result[beam.y][beam.x + 1] == '#'){
						// check if there's a beam there that goes in the same direction to avoid loops
						for (Beam otherBeam : beams) {
							if (otherBeam.x == beam.x + 1 && otherBeam.y == beam.y && otherBeam.direction == beam.direction) {
								activeBeams--;
								beams[i].active = false;
								break;
							}
						}
					}

					if (!beams[i].active) {
						break;
					}

					if (next == '/') {
						beams.push_back({ beam.x + 1, beam.y, UP }); // Current beam goes up
					}
					else if (next == '\\') {
						beams.push_back({ beam.x + 1, beam.y, DOWN }); // Current beam goes down
					}
					else if (next == '|') {
						// Splits
						beams.push_back({ beam.x + 1, beam.y, DOWN }); // Current beam goes down
						beams.push_back({ beam.x + 1, beam.y, UP }); // Current beam goes up
						activeBeams++;
					}
					else if (next == '-') {
						// Keeps going right
						beams.push_back({ beam.x + 1, beam.y, RIGHT });
					}
					else {
						// Keeps going right
						beams.push_back({ beam.x + 1, beam.y, RIGHT });
					}

					beams[i].active = false;
					result[beam.y][beam.x + 1] = '#';

					break;
				case LEFT:
					if (beam.x - 1 < 0) {
						activeBeams--;
						beams[i].active = false;
						break;
					}

					next = map[beam.y][beam.x - 1];

					if (result[beam.y][beam.x - 1] == '#') {
						// check if there's a beam there that goes in the same direction to avoid loops
						for (Beam otherBeam : beams) {
							if (otherBeam.x == beam.x - 1 && otherBeam.y == beam.y && otherBeam.direction == beam.direction) {
								activeBeams--;
								beams[i].active = false;
								break;
							}
						}
					}
					if (!beams[i].active) {
						break;
					}

					if (next == '/') {
						beams.push_back({ beam.x - 1, beam.y, DOWN }); // Current beam goes down
					}
					else if (next == '\\') {
						beams.push_back({ beam.x - 1, beam.y, UP }); // Current beam goes up
					}
					else if (next == '|') {
						// Splits
						beams.push_back({ beam.x - 1, beam.y, DOWN }); // Current beam goes down
						beams.push_back({ beam.x - 1, beam.y, UP }); // Current beam goes up
						activeBeams++;
					}
					else if (next == '-') {
						// Keeps going left
						beams.push_back({ beam.x - 1, beam.y, LEFT });
					}
					else {
						// Keeps going left
						beams.push_back({ beam.x - 1, beam.y, LEFT });
					}

					beams[i].active = false;
					result[beam.y][beam.x - 1] = '#';

					break;
				case UP:
					if (beam.y - 1 < 0) {
						activeBeams--;
						beams[i].active = false;
						break;
					}

					next = map[beam.y - 1][beam.x];

					if (result[beam.y - 1][beam.x] == '#') {
						// check if there's a beam there that goes in the same direction to avoid loops
						for (Beam otherBeam : beams) {
							if (otherBeam.x == beam.x && otherBeam.y == beam.y - 1 && otherBeam.direction == beam.direction) {
								activeBeams--;
								beams[i].active = false;
								break;
							}
						}
					}
					if (!beams[i].active) {
						break;
					}

					if (next == '/') {
						beams.push_back({ beam.x, beam.y - 1, RIGHT }); // Current beam goes right
					}
					else if (next == '\\') {
						beams.push_back({ beam.x, beam.y - 1, LEFT }); // Current beam goes left
					}
					else if (next == '|') {
						beams.push_back({ beam.x, beam.y - 1, UP }); // Keeps going up
					}
					else if (next == '-') {
						// Splits
						beams.push_back({ beam.x, beam.y - 1, RIGHT }); // Current beam goes Right
						beams.push_back({ beam.x, beam.y - 1, LEFT }); // Current beam goes Left
					}
					else{
						// Keeps going up

						beams.push_back({ beam.x, beam.y - 1, UP });
					}
					beams[i].active = false;
					result[beam.y - 1][beam.x] = '#';
					break;
				case DOWN:
					if (beam.y + 1 >= map.size()) {
						activeBeams--;
						beams[i].active = false;
						break;
					}

					next = map[beam.y + 1][beam.x];

					if (result[beam.y + 1][beam.x] == '#') {
						// check if there's a beam there that goes in the same direction to avoid loops
						for (Beam otherBeam : beams) {
							if (otherBeam.x == beam.x && otherBeam.y == beam.y + 1 && otherBeam.direction == beam.direction) {
								activeBeams--;
								beams[i].active = false;
								break;
							}
						}
					}
					if (!beams[i].active) {
						break;
					}

					if (next == '/') {
						beams.push_back({ beam.x, beam.y + 1, LEFT }); // Current beam goes left
					}
					else if (next == '\\') {
						beams.push_back({ beam.x, beam.y + 1, RIGHT }); // Current beam goes right
					}
					else if (next == '|') {
						beams.push_back({ beam.x, beam.y + 1, DOWN }); // Keeps going down
					}
					else if (next == '-') {
						// Splits
						beams.push_back({ beam.x, beam.y + 1, RIGHT }); // Current beam goes Right
						beams.push_back({ beam.x, beam.y + 1, LEFT }); // Current beam goes Left
					}
					else {
						// Keeps going down
						beams.push_back({ beam.x, beam.y + 1, DOWN });
					}

					beams[i].active = false;
					result[beam.y + 1][beam.x] = '#';

					break;
			}

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