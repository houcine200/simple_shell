#include "header.h"

/**
 * _cleaner - Free allocated memory for words and input_copy
 * @words: Array of strings to free
 * @input_copy: String to free
 */

void _cleaner(char **words, char *input_copy)
{
	free(words);
	free(input_copy);
}

/**
 * _prompt - Display a prompt if STDIN is a terminal
 */

void _prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
		write(1, "$ ", 2);
}

/**
 * handle_exit - Handle exit built-in command
 * @words: Array of strings containing command and arguments
 * @input_copy: Copy of the user input
 * @buf: Buffer to free
 * @status: Exit status value
 */

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

/**
 * _handleNonBuiltInCommands - Handle non-built-in commands
 * @words: Array of strings containing command and arguments
 * @input_copy: Copy of the user input
 * @buf: Buffer containing user input
 */

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
 * _strchr - Locate the first occurrence of a character in a string
 * @str: The string to search in
 * @character: The character to search for
 *
 * Return: Pointer to the
 * first occurrence of the character in the string,
 * or NULL if the character is not found.
 */
char *_strchr(const char *str, int character)
{
	size_t i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == character)
		{
			return ((char *)(str + i));
		}
	}

	return (NULL);
}
