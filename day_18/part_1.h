#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

	for (int i = 0; i < length; i++) {
		char *l = lines[i];
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
	}
}