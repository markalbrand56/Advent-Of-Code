#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000
#define CARDS 6

int main() {
  printf("Hello world\n");

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

  int total_cards = 0;
  int cards[line_count];

  for (int i = 0; i < line_count; i++){
    cards[i] = 1;
  }

  for (int i = 0; i < line_count; i++) {
    int current_cards = cards[i];
    for (int h = 0; h < current_cards; h++){

      char *current_line = strdup(lines[i]);
      char *tkn = strtok(current_line, ":");  // Card N

      int winning[100] = {-1}; // Todos inician en -1
      bool finding = false;
      int next_card = i;
    
      int counter = 0;
      int subtotal = 0;

//      printf("\t%s\n", tkn);

      tkn = strtok(NULL, ":");
      char *nums = strtok(tkn, " ");

      while(nums != NULL){
        if (strcmp(nums, "|") == 0){
          finding = true;
          nums = strtok(NULL, " ");
          continue;
        }

        if (finding){
          //printf("Finding: '%s'\n", nums);
          int x = atoi(nums);

          for (int j = 0; j < counter; j++) {
            if (winning[j] == x){
              // Si hay un número ganador, se obtiene una carta nueva
              next_card++;
              cards[next_card] += 1;
            }
          }
  
        } else { // Add to wining
          //printf("'%s'\n", nums);  // Cada número después de 'Card N:'
          int n = atoi(nums);
          winning[counter] = n;
          counter++;
        }
        nums = strtok(NULL, " ");
      } 
    }
  }

  for (int i = 0; i < line_count; i++) {
    printf("Card %i: %i\n", (i+1), cards[i]);
    total_cards += cards[i];
  }

    printf("\nTOTAL: %i\n", total_cards);


  return 0;
}
