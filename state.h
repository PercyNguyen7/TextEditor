#pragma once
#include <stdbool.h>
enum MODES {
  RC = 1,
  RI = 2,
  UK = 3,
  UM = 4,
};
enum USER_RESPONSE {
  YES = 1,
  NO = 2,
  ALL = 3,
  QUIT = 4,
};
enum EXIT_TYPE {
  NORMAL_E = 0,
  QUIT_E = 1,
  NOCHANGE_E = 2,
  ABNORMAL_E = 3,
};
// typedef struct ProgramState {
//   bool match_found;  // if there is at least 1 match in the file
//   bool all_selected; // confirm needed unless all or quit chosen

//   int swap_count; // swap count
//   int total_swap_count;
//   int line_no;            // current line number
//   int total_line_changed; // total lines changed

//   enum USER_RESPONSE user_res; // user response enum (YES, NO, ALL, QUIT)
//   char *new_str;               // pointer to new str (for line processing)
//   char *curr_str;

//   enum MODES mode;
//   char *word;
//   char *file_name;
// } State;
