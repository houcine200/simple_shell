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
 * _strcmp - Compare two strings.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 *
 * Return: 0 if strings are equal, negative if s1 < s2,
 *         and positive if s1 > s2.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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
 * _getenv - Get the value of an environment variable.
 * @name: Name of the environment variable.
 *
 * Return: Pointer to the value of the environment variable.
 *         NULL if the variable doesn't exist.
 */

char *_getenv(const char *name)
{
	size_t nameLen;
	char **env;

	if (name == NULL)
		return (NULL);

	nameLen = _strlen(name);

	for (env = environ; *env != NULL; env++)
	{
		if (_strncmp(*env, name, nameLen) == 0 && (*env)[nameLen] == '=')
		{
			return (*env + nameLen + 1);
		}
	}

	return (NULL);
}
