#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


char *get_location(char *command){
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");

	if (path){
		/* Duplicate the path string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/ 
		path_copy = strdup(path);
		/* Get length of the command that was passed */
		command_length = strlen(command);

		/* Let's break down the path variable and get all the directories available*/
		path_token = strtok(path_copy, ":");

		while(path_token != NULL){
			/* Get the length of the directory*/
			directory_length = strlen(path_token);
			/* allocate memory for storing the command name together with the directory name */
			file_path = malloc(command_length + directory_length + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
			/* to build the path for the command, let's copy the directory path and concatenate the command to it */
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			/* let's test if this file path actually exists and return it if it does, otherwise try the next directory */
			if (stat(file_path, &buffer) == 0){
				/* return value of 0 means success implying that the file_path is valid*/

				/* free up allocated memory before returning your file_path */
				free(path_copy);

				return (file_path);
			}
			else{
				/* free up the file_path memory so we can check for another path*/
				free(file_path);
				path_token = strtok(NULL, ":");

			}

		}

		/* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for path_copy */ 
		free(path_copy);

		/* before we exit without luck, let's see if the command itself is a file_path that exists */
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}


		return (NULL);

	}


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
	return arr;
}
void fork_execve(char **args)
{

	pid_t pid = fork();
	char *command = args[0];
	char *actual_command = NULL;
	actual_command = get_location(command);
	if (pid < 0)
	{
		perror("error fork");
		exit(1);
	}
	if (pid == 0) {
		if (actual_command != NULL) { // Check if the command was found
			if (execve(actual_command, args, NULL) == -1)
				perror("error execve");
		} else {
			fprintf(stderr, "Command not found: %s\n", command);
			exit(2);
		}
	}
	if (pid > 0)
	{
		wait(NULL);
		free(actual_command);
	}
}

int main(void)
{
	char *buf = NULL;
	size_t buf_size = 0;
	ssize_t n_char = 0;
	char **words;
	char *input_copy;

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
		input_copy = strdup(buf);
		words = split(buf);
		fork_execve(words);
		free(words);
		free(input_copy);

	}
	free(buf);

	return (0);
}
