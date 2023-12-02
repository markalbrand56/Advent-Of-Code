#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[])
{
  printf("Hello\n");
  char *numbers_written[10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero"};

  FILE *fp;

  fp = fopen("input.txt", "r");

  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  char *lines[1000];
  int line_count = 0;
  char line[MAX_LINE_LENGTH];

  while(fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    lines[line_count] = strdup(line);

    line_count++;
  }

  int total = 0;

  for (int i = 0; i < line_count; i++) {
    // For each line read
    char *current_line = lines[i];
    char buffer[MAX_LINE_LENGTH];

    for (int j = 0; j < strlen(current_line); j++) {
      // For each char in line
      char current = current_line[j];
      buffer[j] = current;
      int comp = -1;


      for (int h = 0; h < 10; h++) {
        // iterate over the numbers_written
        comp = strcmp(numbers_written[h], buffer);

        if (comp == 0) {
          printf("Line %i num %s\n", i, numbers_written[h]);
        }
      }
    }
    printf("Buffer: %s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
  }

  printf("Total: %d\n", total);

  return 0;
}
