#include "header.h"

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_copy = _strdup(path);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		file_path = malloc(_strlen(command) + 1 + _strlen(path_token) + 1);
		_strcpy(file_path, path_token);
		_strcat(file_path, "/");
		_strcat(file_path, command);
		_strcat(file_path, "\0");

		if (stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		else
		{
			free(file_path);
			path_token = strtok(NULL, ":");
		}
	}
	free(path_copy);

	if (stat(command, &buffer) == 0)
		return (command);

	else
		return (NULL);
}

void fork_execve(char **args, char *buf, char **words, char *input_copy)
{
	pid_t pid = fork();
	char *command = args[0], *actual_command = NULL;
	int status;

	actual_command = get_location(command);
	if (pid < 0)
	{
		perror("error fork");
		_cleaner(words, input_copy);
		free(buf);
		exit(1);
	}
	if (pid == 0)
	{
		if (actual_command != NULL)
		{
			if (execve(actual_command, args, NULL) == -1)
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
		if (actual_command != NULL && actual_command != command)
			free(actual_command);
	}
}

int is_empty_or_whitespace(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
}

int get_built_in(char *str)
{
	int flag = -1;

	if (_strlen(str) == 4 && _strncmp(str, "exit", 4) == 0)
		flag = 0;
	else if (_strlen(str) == 3 && _strncmp(str, "env", 3) == 0)
		flag = 1;
	return (flag);
}

char **split(char *str)
{
	char *token = strtok(str, " \t\n");
	char **arr = malloc(sizeof(*arr) * 1024);
	size_t i = 0;

	for (i = 0; token != NULL; i++)
	{
		arr[i] = token;
		token = strtok(NULL, " \t\n");
	}
	arr[i] = NULL;
	return (arr);
}
