#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "header.h"

void _cleaner(char **words, char *input_copy)
{
	free(words);
	free(input_copy);
}


void _prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
		write(1, "$ ", 2);
}


void handle_exit(char **words, char *input_copy, char *buf, int status)
{
	if (words[1] == NULL)
	{
		_cleaner(words, input_copy);
		free(buf);
		exit(0);
	}
	else if (words[1] != NULL)
	{
		status = _atoi(words[1]);
		_cleaner(words, input_copy);
		free(buf);
		exit(status);
	}
}

void _handleNonBuiltInCommands(char **words, char *input_copy, char *buf)
{
	if (_strcmp(words[0], "setenv") == 0)
	{
		execute_setenv(words);
		_cleaner(words, input_copy);

	}
	else if (_strcmp(words[0], "unsetenv") == 0)
	{
		execute_unsetenv(words);
		_cleaner(words, input_copy);

	}
	else
	{
		fork_execve(words, buf, words, input_copy);
		_cleaner(words, input_copy);
	}
}

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0.
 */

int main(void)
{
	char *buf = NULL, *input_copy;
	size_t buf_size = 0;
	ssize_t n_char = 0;
	char **words;
	int built_in, status = 0;

	while (1)
	{
		_prompt();
		n_char = getline(&buf, &buf_size, stdin);
		if (n_char == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}
		if (buf[0] == '\n')
			continue;
		if (n_char >= 2)
			buf[n_char - 1] = '\0';
		if (is_empty_or_whitespace(buf))
			continue;
		input_copy = _strdup(buf);
		words = split(input_copy);
		built_in = get_built_in(words[0]);
		if (built_in == 0)
			handle_exit(words, input_copy, buf, status);
		else if (built_in == 1)
		{
			execute_env();
			_cleaner(words, input_copy);
			continue;
		}
		else
			_handleNonBuiltInCommands(words, input_copy, buf);
	}
	free(buf);
	return (0);
}
