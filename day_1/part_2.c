#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

char *numbers_written[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int get_value(char number[MAX_LINE_LENGTH]){
  for (int i = 0; i < 10; i++) {
    if (strcmp(number, numbers_written[i]) == 0) {
      return i;
    }
  }
  return -1;
}

int main(int argc, char *argv[])
{
  printf("Hello\n");

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
    int L = -1;
    int R = -1;

    memset(buffer,0,strlen(buffer));
    
    int j2 = 0;

    for (int j = 0; j <= strlen(current_line); j++) {
      // For each char in line
      char current = current_line[j];  // Current character
      buffer[j2] = current;
      //printf("Line %i buffer %s\n", i, buffer);
      j2++;

      if (isdigit(current)){
        R = atoi(&current);

        if (L == -1) {
          L = atoi(&current);
        }
        memset(buffer, 0, sizeof(buffer));
        j2 = 0;
      }

      for (int h = 0; h < 10; h++) {
        // iterate over the numbers_written
        if (strstr(buffer, numbers_written[h]) != NULL) {
          R = get_value(numbers_written[h]);

          if (L == -1) {
            L = get_value(numbers_written[h]);
          }

          // LIMPIAR ACÁ BUFFER
          memset(buffer, 0, sizeof(buffer));
          j2 = 1;
          buffer[0] = current;
        }
      }
    }

    printf("%i. L %i R %i\n", i, L, R);
    total += (L * 10) + R;
  }

  printf("Total: %d\n", total);
  printf("%i\n", get_value("four"));
  return 0;
}
