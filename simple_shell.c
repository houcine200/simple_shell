#include "header.h"

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
	return arr;
}
void fork_execve(char **args)
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("error fork");
		exit(1);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			perror("error execve");
		exit(2);
	}
	if (pid > 0)
	{
		wait(NULL);
	}
}

int main(void)
{
	char *buf;
	size_t buf_size = 0;
	ssize_t n_char = 0;
	char **words;

	while(1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "$ ", 2);
		n_char = getline(&buf, &buf_size, stdin);
		if (n_char == -1) 
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}
		buf[n_char - 1] = '\0';
		char *input_copy = strdup(buf);
		words = split(buf);
		fork_execve(words);
		free(words);
		free(input_copy);
		free(buf);
	}


	return (0);
}
