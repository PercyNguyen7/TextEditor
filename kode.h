#pragma once
#include "state.h"
#include <stdbool.h>

// The program reads the text file line by line and ask processes changes on the
// spot.

enum MODES assign_mode(char *command);
void verify_all_input(char *command, char *word, char *file_name, char *extra);
int start_program(enum MODES mode, char *word, FILE *ftpr);
