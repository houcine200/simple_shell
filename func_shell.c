#include "header.h"

/**
 * get_location - Find the location of a command in the PATH.
 * @command: The command to search for.
 *
 * Return: A pointer to the location of the command, or NULL if not found.
 */
char *get_location(char *command)
{
	char *env_path, *cp_Path, *pathComp, *path_file;
	struct stat file_info;

	env_path = _getenv("PATH");
	if (env_path == NULL)
		return (NULL);

	cp_Path = _strdup(env_path);
	pathComp = strtok(cp_Path, ":");

	while (pathComp)
	{
		path_file = malloc(_strlen(command) + 1 + _strlen(pathComp) + 1);
		_strcpy(path_file, pathComp);
		_strcat(path_file, "/");
		_strcat(path_file, command);
		_strcat(path_file, "\0");

		if (stat(path_file, &file_info) == 0)
		{
			free(cp_Path);
			return (path_file);
		}
		else
		{
			free(path_file);
			pathComp = strtok(NULL, ":");
		}
	}
	free(cp_Path);

	if (stat(command, &file_info) == 0)
		return (command);

	else
		return (NULL);
}

/**
 * fork_execve - Fork and execute a command using execve.
 * @args: The array of arguments for the command.
 * @buf: The buffer containing the command line input.
 * @words: The array of words parsed from the input.
 * @input_copy: A copy of the input buffer.
*/

void fork_execve(char **args, char *buf, char **words, char *input_copy)
{
	pid_t pid = fork();
	char *command = args[0], *full_path = NULL;
	int status;

	full_path = get_location(command);
	if (pid < 0)
	{
		perror("error fork");
		_cleaner(words, input_copy);
		free(buf);
		exit(1);
	}
	if (pid == 0)
	{
		if (full_path != NULL)
		{
			if (execve(full_path, args, NULL) == -1)
			{
				perror("error execve");
				_cleaner(words, input_copy);
				free(buf);
				exit(2);
			}
		}
		else
		{
			write(STDERR_FILENO, "Command not found: ", 19);
			write(STDERR_FILENO, command, _strlen(command));
			write(STDERR_FILENO, "\n", 1);
			_cleaner(words, input_copy);
			free(buf);
			exit(2);
		}
	}
	if (pid > 0)
	{
		wait(&status);
		if (full_path != NULL && full_path != command)
			free(full_path);
	}
}

/**
 * is_empty_or_whitespace - Check if
 * a string is empty or contains only whitespace.
 * @str: The string to check.
 *
 * Return: 1 if the string is empty
 *or contains only whitespace, 0 otherwise.
 */
int is_empty_or_whitespace(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
}

/**
 * get_built_in - Determine if a given command is a built-in command.
 * @str: The command string to check.
 *
 * Return: 0 if the command is "exit"
 * 1 if the command is "env", -1 otherwise.
 */
int get_built_in(char *str)
{
	int flag = -1;

	if (_strlen(str) == 4 && _strncmp(str, "exit", 4) == 0)
		flag = 0;
	else if (_strlen(str) == 3 && _strncmp(str, "env", 3) == 0)
		flag = 1;
	return (flag);
}

/**
 * split - Split a string into an array of words.
 * @str: The string to split.
 *
 * Return: A dynamically allocated array of strings containing the words.
 *         The last element of the array is NULL.
 */
char **split(char *str)
{
	char *token = strtok(str, " \t\n");
	char **array = malloc(sizeof(*array) * 1024);
	size_t i = 0;

	for (i = 0; token != NULL; i++)
	{
		array[i] = token;
		token = strtok(NULL, " \t\n");
	}
	array[i] = NULL;
	return (array);
}
