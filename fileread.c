
#include "fileread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
void check_file(FILE *fptr) {
  if (fptr == NULL) {
    perror("Error opening file: ");
    printf("Exiting program with code 3.\n");
    exit(3);
  }
}
// read_line returns the curr. string or NULL if target line cannot be found
// (target_line > number of lines in txt file)
char *read_line(FILE *fptr) {
  char buffer[MAX_LINE_LENGTH];
  int str_len = 0;
  if (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    str_len = strlen(buffer);
    if (str_len > 0 && buffer[str_len - 1] != '\n') {
      buffer[str_len] = '\n';
      buffer[str_len + 1] = '\0'; // Null-terminate the string
    }
  } else {
    return NULL;
  }
  // return the buffer in a dynamically allocated string
  char *str = (char *)malloc(str_len + 1);
  strcpy(str, buffer);
  return str;
}
//
void write_line(FILE *fptr, char *curr_str, char *new_str) {
  fseek(fptr, -(long)strlen(curr_str), SEEK_CUR);
  fputs(new_str, fptr);
}