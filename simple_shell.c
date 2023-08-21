#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int get_built_in(char *str)
{
	int flag = -1;

	if (strlen(str) == 4 && strncmp(str, "exit", 4) == 0)
		flag = 0;
	else if (strlen(str) == 3 && strncmp(str, "env", 3) == 0)
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

	path_copy = strdup(path);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		file_path = malloc(strlen(command) + 1 + strlen(path_token) + 1);
		strcpy(file_path, path_token);
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
		return(command);

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
void fork_execve(char **args, char *buf, char **words ,char *input_copy)
{

	pid_t pid = fork();
	char *command = args[0];
	char *actual_command = NULL;
	int status;

	actual_command = get_location(command);
	if (pid < 0)
	{
		perror("error fork");
		free(words);
		free(input_copy);
		free(buf);	
		exit(1);
	}
	if (pid == 0)
	{
		if (actual_command != NULL)
		{
			if (execve(actual_command, args, NULL) == -1)
				perror("error execve");
		}
		else
		{
			write(STDERR_FILENO, "Command not found: ", 19);
			write(STDERR_FILENO, command, strlen(command));
			write(STDERR_FILENO, "\n", 1);
			free(words);
			free(input_copy);
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
	extern char **environ;
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
void _cleaner(char **words, char *input_copy) {
	free(words);
	free(input_copy);
}

/**
 * main - shell
 *
 * Return: Always 0.
 */

int main(void)
{
	char *buf = NULL, *input_copy;
	size_t buf_size = 0;
	ssize_t n_char = 0;
	char **words;
	int built_in, status;

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
		// Check if the input consists of only spaces or tabs
		int i;
		int only_whitespace = 1; // Assume it contains only whitespace
		for (i = 0; buf[i] != '\0'; i++)
		{
			if (buf[i] != ' ' && buf[i] != '\t')
			{
				only_whitespace = 0; // Contains non-whitespace character
				break;
			}
		}

		// Handle the case of empty or whitespace-only line.
		if (buf[0] == '\0' || only_whitespace)
			continue;
		input_copy = strdup(buf);
		words = split(input_copy);
		built_in = get_built_in(words[0]);
		if (built_in == 0)
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
		else if (built_in == 1)
		{
			execute_env();
			_cleaner(words, input_copy);
			continue;
		}
		fork_execve(words, buf, words, input_copy);
		_cleaner(words, input_copy);
	}
	free(buf);
	return (0);
}
