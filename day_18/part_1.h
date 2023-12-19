#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct coord {
	int x;
	int y;
};

void part_1() {
	printf("Part 1\n");

	FILE *fp;

	fp = fopen("sample.txt", "r");

	if (fp == NULL) {
		printf("Error opening file\n");
		return;
	}

	char *lines[1000];
	int length = 0;
	char line[1000];

	while(fgets(line, 1000, fp) != NULL) {
		line[strcspn(line, "\n")] = '\0';

		lines[length] = strdup(line);

		length++;
	}

	fclose(fp);

	int input_coords = 0;

	for (int i = 0; i < length; i++) {
		char *l = strdup(lines[i]);

		char *parts[3];
		int part_length = 0;
		char *part = strtok(l, " ");
		while (part != NULL) {
			parts[part_length] = strdup(part);
			part_length++;
			part = strtok(NULL, " ");
		}

		input_coords += atoi(parts[1]);

		free(parts[0]);
		free(parts[1]);
		free(parts[2]);

	}

	printf("Total: %d\n", input_coords);

	struct coord borders[input_coords];
	borders[0] = (struct coord) {0, 0};
	int k = 0;

	for (int i = 0; i < length; i++) {
		char *l = strdup(lines[i]);
		printf("%s\n", l);

		char *parts[3];
		int part_length = 0;
		char *part = strtok(l, " ");
		while (part != NULL) {
			parts[part_length] = strdup(part);
			part_length++;
			part = strtok(NULL, " ");
		}

		printf("%s-%s-%s\n", parts[0], parts[1], parts[2]);

		char direction = *parts[0];
		int distance = atoi(parts[1]);

		for(int j = 0; j < distance; j++) {
			if (direction == 'R') {
				borders[k + 1] = (struct coord) {borders[k].x + 1, borders[k].y};
			} else if (direction == 'L') {
				borders[k + 1] = (struct coord) {borders[k].x - 1, borders[k].y};
			} else if (direction == 'U') {
				borders[k + 1] = (struct coord) {borders[k].x, borders[k].y + 1};
			} else if (direction == 'D') {
				borders[k + 1] = (struct coord) {borders[k].x, borders[k].y - 1};
			}

			k++;
		}

		free(parts[0]);
		free(parts[1]);
		free(parts[2]);
	}

	int min_x = 0;
	int max_x = 0;
	int min_y = 0;
	int max_y = 0;

	for (int i = 0; i < input_coords; i++) {
		if (borders[i].x < min_x) {
			min_x = borders[i].x;
		}
		if (borders[i].x > max_x) {
			max_x = borders[i].x;
		}
		if (borders[i].y < min_y) {
			min_y = borders[i].y;
		}
		if (borders[i].y > max_y) {
			max_y = borders[i].y;
		}
	}

	printf("Min: %d, %d\n", min_x, min_y);
	printf("Max: %d, %d\n", max_x, max_y);

	int area = 0;
	for (int i = min_y; i <= max_y; i++) {
		for (int j = min_x; j <= max_x; j++) {
			// Find if this coord is either in the borders array or inside the figure
			// To be inside the figure, it must be able to reach a coord in the borders array in each direction
			// If it can, then it is inside the figure

			struct coord current = (struct coord) {j, i};

			int left = 0;
			int right = 0;
			int up = 0;
			int down = 0;


		}
	}

}