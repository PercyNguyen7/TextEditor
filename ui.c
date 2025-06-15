
#include "ui.h"
#include "fileread.h"
#include "wreplace.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// get_response processes user's response and return a number corresponding to
// an action 1: YES, 2: NO, 3: ALL, 4: QUIT
enum USER_RESPONSE get_response() {
  while (true) {
    char res[100];
    scanf("%20s", res);
    to_lowercase_in_place(res);
    if (strcmp(res, "yes") == 0 || strcmp(res, "y") == 0) {
      return YES;
    } else if (strcmp(res, "no") == 0 || strcmp(res, "n") == 0) {
      return NO;
    } else if (strcmp(res, "all") == 0 || strcmp(res, "a") == 0) {
      return ALL;
    } else if (strcmp(res, "quit") == 0 || strcmp(res, "q") == 0) {
      return QUIT;
    }
    printf(
        "\nPlease input a valid answer (Yes (y), No (n), All (a), Quit (q))\n");
  }
}
void display_welcome_msg(enum MODES mode) {
  switch (mode) {
  case RC:
    printf(
        "\n---------------Redacting Word Case Sensitive-----------------\n\n");
    break;
  case RI:
    printf(
        "\n------------------Redacting Word Case Ignored-----------------\n\n");
    break;
  case UK:
    printf(
        "\n------------------Unmatching Word Keep Case-------------------\n\n");
    break;
  case UM:
    printf(
        "\n----------------Unmatching Word Special Case------------------\n\n");
    break;
  };
}

void display_summary(int total_swap_count, int total_line_changed,
                     enum EXIT_TYPE exit_type) {
  printf("-------------------------SUMMARY--------------------------\n\n");

  if (exit_type == NORMAL_E) {
    printf("Changed %d word(s) in %d line(s). Exiting normally and returning "
           "code 0.\n\n",
           total_swap_count, total_line_changed);
  } else if (exit_type == QUIT_E) {
    printf("Changed %d word(s) in %d line(s). Exiting normally and returning "
           "code 1.\n\n",
           total_swap_count, total_line_changed);
  } else if (exit_type == NOCHANGE_E) {
    printf("No match found. Exiting normally and returning code 2.\n\n");
  }

  printf("---------------------SEE YOU NEXT TIME----------------------\n\n");
}

void display_change_instruction(int line_no, char *curr_str, char *new_str) {
  printf("Changing line %d from\n%sto\n%sConfirm (Yes (y), No (n), All "
         "(a), Quit (q))? _\n",
         line_no, curr_str, new_str);
}