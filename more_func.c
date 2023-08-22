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
/**
 * _atoi - converts a string to an integer.
 * @s: the string to convert
 * Return: the converted string.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int num = 0;

	for (; s[0] != '\0'; s++)
	{
		if (s[0] == '-')
			sign = -sign;

		else if (s[0] >= '0' && s[0] <= '9')
			num = (num * 10) + (s[0] - '0');

		else if (num > 0)
			break;
	}
	return (num * sign);
}
/**
 * _strcmp - compares two strings, ending at the first byte that is different.
 * @s1: string to be compared
 * @s2: string to compare by
 * Return: the difference between the first character that are not the same
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]; i++)
		;
	return (s1[i] - s2[i]);
}
