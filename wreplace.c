#include "wreplace.h"

#include <ctype.h> // for character type
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function return the encoded version of the word by matching the # of * with
// the word's length
char *censorWord(char *word) {
  // Making censored word from input word
  int len = strlen(word);
  char *censored_word = (char *)malloc((len + 1) * sizeof(char));
  if (censored_word == NULL) {
    fprintf(stderr, "Memory allocation failed for string. Exiting program.\n");
    exit(ABNORMAL_E);
  }
  // Change each character to a *
  for (int i = 0; i < len; i++) {
    censored_word[i] = '*';
    if (i == len - 1) {
      censored_word[i + 1] = '\0';
    }
  }
  return censored_word;
}

// Using the first char pointer and changing its character to lowercase
void to_lowercase_in_place(char *str) {
  while (*str) {
    *str = tolower(*str);
    str++;
  }
}
// fn return a dynamic string that is lower case of given str
char *to_lowercase(char *str) {
  int len = 0;
  while (str[len] != '\0')
    len++;

  char *lowercase_str = (char *)malloc(len + 1);
  if (lowercase_str == NULL) {
    fprintf(stderr, "Memory allocation failed for string. Exiting program.\n");
    exit(ABNORMAL_E);
  }

  for (int i = 0; i < len; i++) {
    lowercase_str[i] = tolower(str[i]); // Convert each char to lowercase
  }
  lowercase_str[len] = '\0';
  return lowercase_str;
}

// function turns provided string to be uppercase
char *to_uppercase(char *str) {
  int len = 0;
  while (str[len] != '\0')
    len++;

  char *uppercase_str = (char *)malloc(len + 1);
  if (uppercase_str == NULL) {
    fprintf(stderr, "Memory allocation failed for string. Exiting program.\n");
    exit(ABNORMAL_E);
  }

  for (int i = 0; i < len; i++) {
    uppercase_str[i] = toupper(str[i]); // convert each char to uppercase
  }
  uppercase_str[len] = '\0';
  return uppercase_str;
}

// function checks if the censored version (****) of the word  is found in
// string
bool encoded_word_found(char *str, char *word) {
  char *censored_word = censorWord(word);
  char *temp = str;
  size_t len2 = strlen(censored_word);

  while (*temp) {
    // check if the substring from current position matches word
    if (strncmp(temp, censored_word, len2) == 0) {
      // ensure # of * is exact, no more and no less
      // check if im at beginning of string, and if not is there a * in the char
      // before temp
      if ((temp == str || *(temp - 1) != '*') && *(temp + len2) != '*') {
        free(censored_word);
        return true;
      }
    }
    temp++;
  }
  free(censored_word);
  return false;
}

// substring logic differs for each command (i.e mode)
bool word_found(enum MODES mode, char *str, char *word) {
  switch (mode) {
  case RC:
    return strstr(str, word) != NULL;
    break;
  case RI:
    char *lower_str = to_lowercase(str);
    char *lower_word = to_lowercase(word);
    char *res = strstr(lower_str, lower_word);
    free(lower_str);
    free(lower_word);
    return res != NULL;
    break;
  case UK:
  case UM:
    return encoded_word_found(str, word);
    break;
  }
  return false;
}

// Logic for RC
// function encodes all words (transforming word to ****), then return the
// resulting string dynamically
char *redact_word(char *before, char *word, int *pt_swap_count) {
  char *censored_word = censorWord(word);
  int word_length = strlen(word);
  int before_length = strlen(before);

  // stores pointer to the dynamically allocated after string
  char *after;
  after = malloc((before_length + 1) * sizeof(char));
  if (after == NULL) {
    fprintf(stderr, "Memory allocation failed for string. Exiting program.\n");
    exit(ABNORMAL_E);
  }
  // i is index of before
  int i = 0;

  // again we loop through the before string, just as above, but now we
  // will build the after string as we do so
  while (i < strlen(before)) {
    // if substring found, copy word to new string, then increment i by word_len
    if (strstr(&before[i], word) == &before[i]) {
      strcpy(&after[i], censored_word);
      i += word_length;

      if (pt_swap_count != NULL)
        *pt_swap_count += 1; // increment swap count
    }
    // else we just copy exactly from before to after str
    else {
      after[i] = before[i];
      i++;
    }
  }
  after[i] = '\0';
  free(censored_word);
  // return a pointer to the after string
  return after;
}

// Logic for RI.
// function encodes all words (transforming word to ****) while ignoring case,
// then return the resulting string dynamically
char *redact_word_ignorecase(char *before, char *word, int *pt_swap_count) {
  int word_length = strlen(word);
  int before_length = strlen(before);
  char *lower_word = to_lowercase(word);
  char *lower_before = to_lowercase(before);
  char *censored_word = censorWord(word);
  char *after;

  after = malloc((before_length + 1) * sizeof(char));
  if (after == NULL) {
    fprintf(stderr, "Memory allocation failed for string. Exiting program.\n");
    exit(ABNORMAL_E);
  }
  int i = 0;

  while (i < strlen(before)) {
    if (strstr(&lower_before[i], lower_word) == &lower_before[i]) {
      strcpy(&after[i], censored_word);
      i += word_length;
      if (pt_swap_count != NULL)
        *pt_swap_count += 1;
    }

    else {
      after[i] = before[i];
      i++;
    }
  }

  after[i] = '\0';
  free(censored_word);
  free(lower_word);
  free(lower_before);
  // return a pointer to the after string
  return after;
}

// Logic for UK.
// function replaces all encoded words (i.e ***) with the given word, then
// return the resulting string dynamically
char *decode_word_keep_case(char *before, char *word, int *pt_swap_count) {
  int word_len = strlen(word);
  int before_length = strlen(before);
  char *censored_word = censorWord(word);

  // stores pointer to the dynamically allocated after string
  char *after;

  after = malloc((before_length + 1) * sizeof(char));
  if (after == NULL) {
    fprintf(stderr, "Memory allocation failed for string. Exiting program.\n");
    exit(ABNORMAL_E);
  }
  int i = 0;

  while (i < strlen(before)) {
    if (strstr(&before[i], censored_word) == &before[i] &&
        ((i == 0) || before[i - 1] != '*') && before[i + word_len] != '*') {

      strcpy(&after[i], word);
      i += word_len;

      if (pt_swap_count != NULL)
        *pt_swap_count += 1;
    } else {
      after[i] = before[i];
      i++;
    }
  }

  after[i] = '\0';
  free(censored_word);
  // return a pointer to the after string
  return after;
}

// Logic for UM.
// function replaces all encoded words (i.e ***) with the given word, then
// return the resulting string dynamically. the word replaced has the same case
// as the letter before, if none then the same case as the letter after, if none
// then the the same case as the word provided. EX: These ***S are so funny!
// Result: These CATS are so funny! (S is uppercase)
char *decode_word_match_case(char *before, char *word, int *pt_swap_count) {
  // get the lengths of the before string, old substring and new substring
  int word_len = strlen(word);
  int before_length = strlen(before);
  char *censored_word = censorWord(word);
  char *upper_word = to_uppercase(word);
  char *lower_word = to_lowercase(word);
  // stores pointer to the dynamically allocated after string
  char *after;

  after = malloc((before_length + 1) * sizeof(char));
  int i = 0;

  while (i < strlen(before)) {
    int prevInd = i - 1;
    int afterInd = i + word_len; // index right after the word on that string
    if (strstr(&before[i], censored_word) == &before[i] &&
        ((i == 0) || before[i - 1] != '*') && before[i + word_len] != '*') {
      // if prevInd is in bounds and the character is a letter
      if (prevInd >= 0 && prevInd <= (before_length - 2) &&
          isalpha(before[prevInd])) {
        if (isupper(before[prevInd])) {
          strcpy(&after[i], upper_word);
        } else {
          strcpy(&after[i], lower_word);
        }
      }
      // if afterInd is in bounds and the character is a letter
      else if (afterInd >= 1 && (afterInd <= before_length - 1) &&
               isalpha(before[afterInd])) {
        if (isupper(before[i + word_len])) {
          strcpy(&after[i], upper_word);
        } else {
          strcpy(&after[i], lower_word);
        }
      }
      // if no before or after letter, then
      else {
        strcpy(&after[i], word);
      }

      i += word_len;

      if (pt_swap_count != NULL)
        *pt_swap_count += 1;
    } else {
      after[i] = before[i];
      i++;
    }
  }
  // put a null terminator at the end of the after string
  after[i] = '\0';
  free(censored_word);
  free(lower_word);
  free(upper_word);
  // return a pointer to the after string
  return after;
}
// function processes and return the string according to the given mode
char *process_string(enum MODES mode, char *curr_str, char *word,
                     int *pt_swap_count) {
  switch (mode) {
  case 1:
    return redact_word(curr_str, word, pt_swap_count);
    break;
  case 2:
    return redact_word_ignorecase(curr_str, word, pt_swap_count);
    break;
  case 3:
    return decode_word_keep_case(curr_str, word, pt_swap_count);
    break;

  case 4:
    return decode_word_match_case(curr_str, word, pt_swap_count);
    break;
  }
  return NULL;
}
