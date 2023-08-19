#include "header.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: Pointer to the input string.
 *
 * Return: The length of the string.
 */

int _strlen(char *s)
{
	int l;

	for (l = 0; s[l] != '\0'; l++)
	{
	}
	return (l);
}

/**
 * _strdup - copies a string into a new buffer
 * @str: the string to copy
 * Return: pointer to a new buffer
 */

char *_strdup(char *str)
{
	unsigned int i;
	char *dest;

	if (str == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * (strlen(str) + 1));

	if (dest == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		dest[i] = str[i];

	dest[i] = '\0';
	return (dest);
}

/**
 *_strcpy - Copies a string from source to destination.
 *@dest: Pointer to the destination string.
 *@src: Pointer to the source string.
 *Return: Pointer to the destination string.
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 *_strcat - Concatenates two strings.
 *@dest: Pointer to the destination string.
 *@src: Pointer to the source string to be concatenated.
 *Return: Pointer to the destination string after concatenation.
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i++] = src[j];
	}
	return (dest);
}

/**
 * _strncmp - Compare two strings within a specified length
 * @s1: The first string to compare
 * @s2: The second string to compare
 * @n: The maximum number of characters to compare
 *
 * Description:
 * Compare the first n characters of two strings, s1 and s2.
 * Return an integer less than, equal to, or greater than zero
 * if the first differing character is less than, equal to,
 * or greater than the corresponding character in the other string.
 *
 * Return: An integer less than, equal to, or greater than zero
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return (unsigned char)s1[i] - (unsigned char)s2[i];
		}
		if (s1[i] == '\0')
		{
			return 0;
		}
	}
	return 0;
}
