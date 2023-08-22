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

int get_built_in(char *str)
{
	int flag = -1;

	if (_strlen(str) == 4 && strncmp(str, "exit", 4) == 0)
		flag = 0;
	else if (_strlen(str) == 3 && strncmp(str, "env", 3) == 0)
		flag = 1;
	return (flag);
}

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_copy = _strdup(path);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		file_path = malloc(_strlen(command) + 1 + _strlen(path_token) + 1);
		_strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);
		strcat(file_path, "\0");

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

void execute_env(void)
{
	int i;
	char **env = environ;

	for (i = 0; env[i] != NULL; i++)
	{
		puts(env[i]);

	}
}

void _prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
		write(1, "$ ", 2);
}


int is_empty_or_whitespace(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
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
		status = atoi(words[1]);
		_cleaner(words, input_copy);
		free(buf);
		exit(status);
	}
}
void execute_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", _strlen("Usage: setenv VARIABLE VALUE\n"));
		return;
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}
}
void execute_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", _strlen("Usage: unsetenv VARIABLE\n"));
		return;
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
	}
}
int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_var;
	int i;

	if (!name || !value)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, _strlen(name)) == 0)
		{
			if (overwrite)
			{
				new_var = malloc(_strlen(name) + _strlen(value) + 2);
				_strcpy(new_var, name);
				strcat(new_var, "=");
				strcat(new_var, value);
				environ[i] = new_var;
				return (0);
			}
			return (0);
		}
	}
	new_var = malloc(_strlen(name) + _strlen(value) + 2);
	_strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}
int _unsetenv(const char *name)
{
	int i, j = 0;

	if (!name || name[0] == '\0' || strchr(name, '=') != NULL)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, _strlen(name)) == 0
				&& environ[i][_strlen(name)] == '=')
		{
			free(environ[i]);

			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}

			return (0);
		}
	}

	return (0);
}
void _handleNonBuiltInCommands(char **words, char *input_copy, char *buf)
{
	if (strcmp(words[0], "setenv") == 0)
	{
		execute_setenv(words);
		_cleaner(words, input_copy);

	}
	else if (strcmp(words[0], "unsetenv") == 0)
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
