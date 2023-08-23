#include "header.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0.
 */

int main(void)
{
	char *buf = NULL, *input_copy;
	size_t size_buf = 0;
	ssize_t nb_chars = 0;
	char **words;
	int built_in, status = 0;

	while (1)
	{
		_prompt();
		nb_chars = getline(&buf, &size_buf, stdin);
		if (nb_chars == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}
		if (buf[0] == '\n')
			continue;
		if (nb_chars >= 2)
			buf[nb_chars - 1] = '\0';
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
