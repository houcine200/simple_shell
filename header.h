#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int get_built_in(char *str);
char *get_location(char *command);
char **split(char *str);
void fork_execve(char **args);
void execute_env();

int _putchar(char c);
void _puts(char *str);
char *_getenv(char *name);

int _strlen(char *s);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
#endif
