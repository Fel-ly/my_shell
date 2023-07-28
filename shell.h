#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdbool.h>

int main(int ac, char *av[], char **env);
int execute(char *arguments[], struct stat *statbuf, char **env);
bool check_file_status(char *pathname, struct stat *statbuf);
void handle_error(pid_t pid);
char **split_string(char *str, const char *delimiter, int *argc);

#endif
