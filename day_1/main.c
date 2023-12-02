#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

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
    char *current_line = lines[i];

    int L = -1;
    int R = -1;

    for (int j = 0; j < strlen(current_line); j++) {
      char current = current_line[j];

      if (isdigit(current)){
        if (L < 0){
          L = atoi(&current);
        }
        R = atoi(&current);
      }
    }

    printf("N = %d%d\n", L, R);

    total += (10 * L)+R;

  }

  printf("Total: %d\n", total);

  return 0;
}
