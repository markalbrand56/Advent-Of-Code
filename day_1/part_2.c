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
    char L[MAX_LINE_LENGTH];
    char R[MAX_LINE_LENGTH];

    memset(buffer,0,strlen(buffer));
    memset(L, 0, strlen(L));
    memset(R, 0, strlen(R));
    int j2 = 0;

    for (int j = 0; j <= strlen(current_line); j++) {
      // For each char in line
      char current = current_line[j];  // Current character
      buffer[j2] = current;

      j2++;

      for (int h = 0; h < 10; h++) {
        // iterate over the numbers_written
        if (strstr(buffer, numbers_written[h]) != NULL) {
          strcpy(R, numbers_written[h]);

          if (L[0] == '\0') {
            strcpy(L, numbers_written[h]);
            //printf("Copied L %s\n", L);
          }

          // LIMPIAR ACÁ BUFFER
          memset(buffer, 0, sizeof(buffer));
          j2 = 0;
        }
      }
    }
    printf("L %s R %s\n", L, R);
  }

  printf("Total: %d\n", total);

  return 0;
}
