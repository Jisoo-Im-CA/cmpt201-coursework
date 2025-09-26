#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _POSIX_C_SOURCE 200809L
#define MAX_LEN 5

char *history[MAX_LEN];
int history_count = 0;

char *get_input();
void add_to_history(char *input);
void print_history();

int main() {
  while (1) {
    char *input = get_input();
    add_to_history(input);
    if (strcmp(input, "print") == 0) {
      print_history();
    }
  }
  return 0;
}

char *get_input() {
  char *buffer = NULL;
  size_t bufsize = 0;
  printf("Enter input: ");
  ssize_t len = getline(&buffer, &bufsize, stdin);
  if (len == -1)
    exit(1);
  buffer[len - 1] = '\0';
  return buffer;
}

void add_to_history(char *input) {
  if (history_count < MAX_LEN) {
    history[history_count++] = input;
  } else {
    free(history[0]);
    for (int i = 1; i < MAX_LEN; i++) {
      history[i - 1] = history[i];
    }
    history[MAX_LEN - 1] = input;
  }
}

void print_history() {
  printf("history:\n");
  for (int i = 0; i < history_count; i++) {
    printf("%s\n", history[i]);
  }
}
