
#pragma once

#include "state.h"
#include <stdbool.h>

enum USER_RESPONSE get_response();
void display_welcome_msg(enum MODES mode);
void display_summary(int total_swap_count, int total_line_changed,
                     enum EXIT_TYPE exit_type);
void display_change_instruction(int line_no, char *curr_str, char *new_str);
