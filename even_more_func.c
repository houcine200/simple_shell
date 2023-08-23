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
