#include "header.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string, followed by a new line.
 * @str: input string to print.
 */
void _puts(char *str)
{
	int l;

	for (l = 0; str[l] != '\0'; l++)
	{
		_putchar(str[l]);
	}
	_putchar('\n');
}
/**
 * _getenv - Custom implementation of the getenv function.
 * @name: The name of the environment variable to search for.
 *
 * Description:
 * This function searches for the value of the specified environment variable.
 *
 * Return: A pointer to the value of the environment variable if found, or NULL if not found.
 */
char *_getenv(char *name)
{
	extern char **environ;
	char *key;
	int i;
	
	if (name == NULL)
		return NULL;

	for (i = 0; environ[i] != NULL; i++)
	{
		key = strtok(environ[i], "=");

		if (strcmp(key, name) == 0)
			return (strtok(NULL, "="));
	}
	return NULL;
}
