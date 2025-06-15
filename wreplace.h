#pragma once

#include "state.h"

#include <stdbool.h>

// helper functions
void to_lowercase_in_place(char *str);
char *to_lowercase(char *word);
char *to_uppercase(char *word);
char *censorWord(char *word);
bool encoded_word_found(char *string, char *substring);
bool word_found(enum MODES mode, char *str, char *word);

// major functions
char *process_string(enum MODES mode, char *curr_string, char *word,
                     int *pt_swap_count);
char *redact_word(char *str, char *word, int *wordCount);
char *redact_word_ignorecase(char *before, char *word, int *pt_swap_count);
char *decode_word_keep_case(char *before, char *word, int *pt_swap_count);
char *decode_word_match_case(char *before, char *word, int *pt_swap_count);
