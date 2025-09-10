#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  char *buff = NULL;
  size_t len = 0;
  ssize_t nread;
  const char *delim = " ";
  char *saveptr;

  printf("Please enter some text: ");

  nread = getline(&buff, &len, stdin);

  if (nread == -1) {
    printf("getline failed");
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  char *ret = strtok_r(buff, delim, &saveptr);

  printf("Token: \n");

  while (ret != NULL) {
    printf("%s\n", ret);
    ret = strtok_r(NULL, delim, &saveptr);
  }
  free(buff);

  return 0;
}
