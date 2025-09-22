#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argc;

  char *line = NULL;
  size_t n = 0;

  printf("Enter programs to run.\n");

  for (;;) {
    ssize_t len = getline(&line, &n, stdin);
    if (len == -1) {
      if (errno != 0) {
        perror("Fail to enter");
      }
      break;
    } else if (len > 0) {
      line[len - 1] = '\0';
    }

    printf("Executing:\"%s\"\n", line);

    pid_t pid = fork();

    if (pid) {
      int status = 0;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(status)) {
        printf("Child exited.\n");

      } else {
        if (execl(line, line, (char *)NULL) == -1) {
          perror("execl");
          exit(EXIT_FAILURE);
        }
      }
    }

    free(line);

    return 0;
  }
}
