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
int _strcmp(const char *s1, const char *s2) 
{
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
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
char *_getenv(const char *name) 
{
    if (name == NULL) {
        return NULL;
    }

    size_t nameLen = strlen(name);

    for (char **env = environ; *env != NULL; env++) {
        if (strncmp(*env, name, nameLen) == 0 && (*env)[nameLen] == '=') {
            return *env + nameLen + 1;  // Return value after '=' character
        }
    }

    return NULL;  // Variable not found
}
