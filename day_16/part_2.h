#include <iostream>
#include "reader.h"

using namespace std;

void part_2(){
	cout << "\nPart 2" << endl;

	Reader reader("input.txt");

	vector<string> map = reader.getContents();

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

	Start: any edge tile and heading away from that edge
	 	You can choose either of two directions for the beam if it starts on a corner

	Wherever a beam pases, it becomes energized ('.' -> '#')
	The beams will continue until they hit a splitter or a corner

	 */

	vector<Beam> startingBeams;
	long long max_energized = 0;

	// Find all starting beams
	// Top edges: Top to bottom
	for (int column = 0; column < map[0].size(); column++){
		startingBeams.push_back({ column, 0, DOWN });
	}

	// Bottom edges: Bottom to top
	for (int column = 0; column < map[0].size(); column++) {
		startingBeams.push_back({ column, static_cast<int>(map.size() - 1), UP });
	}

	// Left edges: Left to right
	for (int row = 0; row < map.size(); row++) {
		startingBeams.push_back({ 0, row, RIGHT });
	}

	// Right edges: Right to left
	for (int row = 0; row < map.size(); row++) {
		startingBeams.push_back({ static_cast<int>(map[0].size() - 1), row, LEFT });
	}

	for (Beam starting_beam : startingBeams) {
		vector<string> result = map;

		// Clean the result map
		for (int i = 0; i < result.size(); i++) {
			string line = result[i];
			for (int j = 0; j < line.size(); j++) {
				char c = line[j];
				if (c == '\\' || c == '/' || c == '-' || c == '|') {
					result[i][j] = '.';
				}
			}
		}

		vector<Beam> beams;
		int activeBeams = 1;

		beams.push_back(starting_beam);

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

		int count = 0;
		for (string line : result) {
			for (char c : line) {
				if (c == '#') {
					count++;
				}
			}
		}

		if (count > max_energized) {
			max_energized = count;
		}

	}

	cout << "Max energized: " << max_energized << endl;

}