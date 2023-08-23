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
 * _puts - prints a string. followed by a new line.
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
	int i, j;

	for (i = 0, j = 0; s1[i] && s1[i] == s2[j]; i++, j++)
		;

	return (*(unsigned char *)&s1[i] - *(unsigned char *)&s2[j]);
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
	size_t name_l, j;
	int i;
	char **env_copy;

	if (name == NULL)
		return (NULL);

	name_l = _strlen(name);

	env_copy = environ;

	for (i = 0; env_copy[i] != NULL; i++)
	{
		for (j = 0; env_copy[i][j] != '\0' &&
				j < name_l && env_copy[i][j] == name[j]; j++)
			;

		if (j == name_l && env_copy[i][j] == '=')
		{
			return (env_copy[i] + name_l + 1);
		}
	}

	return (NULL);
}
