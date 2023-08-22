#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

int get_built_in(char *str);
char *get_location(char *command);
char **split(char *str);
void fork_execve(char **args, char *buf, char **words, char *input_copy);
void execute_env(void);
void _prompt(void);
void _cleaner(char **words, char *input_copy);
int is_empty_or_whitespace(const char *str);
void handle_exit(char **words, char *input_copy, char *buf, int status);
void execute_setenv(char **args);
void execute_unsetenv(char **args);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void _handleNonBuiltInCommands(char **words, char *input_copy, char *buf);

int _putchar(char c);
void _puts(char *str);
char *_getenv(char *name);
int _atoi(char *s);
int _strcmp(char *s1, char *s2);

int _strlen(char *s);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);


#endif
