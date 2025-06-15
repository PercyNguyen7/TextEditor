#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileread.h"
#include "kode.h"
#include "state.h"
#include "ui.h"
#include "wreplace.h"

// kode.c contains functions to verify the command and the word input.
int main(int argc, char *argv[]) {
  verify_all_input(argv[1], argv[2], argv[3], argv[4]);

  enum MODES mode = assign_mode(argv[1]);
  char *word = argv[2];
  char *file_name = argv[3];

  // open a file in read mode
  FILE *fptr = fopen(file_name, "r+");
  check_file(fptr);

  int exit_code = start_program(mode, word, fptr);
  return (exit_code);
}

// start_program executes the entire logic of the program
int start_program(enum MODES mode, char *word, FILE *fptr) {
  // UI
  bool match_found = false;  // if there is at least 1 match in the file
  bool all_selected = false; // confirm needed unless all or quit chosen
  enum USER_RESPONSE user_res;

  // Program State
  int total_swap_count = 0;
  int line_no = 0;
  int total_line_changed = 0;
  char *curr_str = NULL;

  display_welcome_msg(mode);
  // Looping through each line from the txt file
  while ((curr_str = read_line(fptr)) != NULL) {
    // IF the word/encoded word can be replaced!
    if (word_found(mode, curr_str, word)) {
      int swap_count = 0;
      int *pt_swap_count = &swap_count;
      char *new_str = process_string(mode, curr_str, word, pt_swap_count);
      match_found = true;

      if (!all_selected) {
        display_change_instruction(line_no, curr_str, new_str);
        user_res = get_response();
      }

      switch (user_res) {
      case YES:
        total_swap_count += swap_count;
        total_line_changed++;
        write_line(fptr, curr_str, new_str);
        printf("The word(s) %s on line %d were changed.\n\n", word, line_no);
        break;
      case NO:
        printf("No change was made on line #%d!\n\n", line_no);
        break;
      case ALL:
        total_swap_count += swap_count;
        total_line_changed++;
        write_line(fptr, curr_str, new_str);
        if (!all_selected) {
          printf("All remaining word(s) %s have been changed.\n\n", word);
          all_selected = true;
        }
        break;
      case QUIT:
        free(curr_str);
        free(new_str);
        fclose(fptr);
        printf("Quitting the program without further changes.");
        display_summary(total_swap_count, total_line_changed, QUIT_E);
        return QUIT_E;
      }
      free(new_str);
    } else {
      if (!all_selected) {
        printf("No change needed on line #%d!\n\n", line_no);
      }
    }
    line_no++;
    free(curr_str);
  }
  fclose(fptr);
  match_found
      ? display_summary(total_swap_count, total_line_changed, NORMAL_E)
      : display_summary(total_swap_count, total_line_changed, NOCHANGE_E);
  return match_found ? NORMAL_E : NOCHANGE_E;
}

// function verifies if the given command is valid
enum MODES assign_mode(char *command) {
  if (strcmp(command, "RC") == 0) {
    return RC;
  } else if (strcmp(command, "RI") == 0) {
    return RI;
  } else if (strcmp(command, "UK") == 0) {
    return UK;
  } else if (strcmp(command, "UM") == 0) {
    return UM;
  } else {
    printf("\nThat is not a valid task command. Closing the application and "
           "returning code 3\n\n");
    exit(ABNORMAL_E);
  }
}

// function verifies if there are exactly 3 inputs in the command
void verify_all_input(char *command, char *word, char *file_name, char *extra) {
  if (command == NULL) {
    printf("Missing command. Exiting the application and returning code 3.\n");
    exit(ABNORMAL_E);
  }
  if (word == NULL) {
    printf(
        "Missing word input. Exiting the application and returning code 3.\n");
    exit(ABNORMAL_E);
  }
  if (file_name == NULL) {
    printf("Missing text file name. Exiting the application and returning code "
           "3.\n");
    exit(ABNORMAL_E);
  }
  if (extra != NULL) {
    printf(
        "Too many arguments. Exiting the application and returning code 3.\n");
    exit(ABNORMAL_E);
  }
}