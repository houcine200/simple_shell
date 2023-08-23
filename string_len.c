#include "header.h"
/**
 * _strlen - calculates the length of a string.
 * @s: pointer to the character array.
 * Return: length of the string
 */
int _strlen(const char *s)
{
	int l;

	for (l = 0; s[l] != '\0'; l++)
		;
	return (l);
}

/**
 * _strdup - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the newly allocated duplicated string,
 *         NULL if str is NULL or if memory allocation fails.
 */
char *_strdup(char *str)
{
	int len, j;
	char *buff;

	if (str == NULL)
		return (NULL);

	for (len = 0; str[len] != '\0'; len++)
		;

	buff = malloc(sizeof(char) * (len + 1));
	if (buff == NULL)
		return (NULL);

	for (j = 0; str[j] != '\0'; j++)
		buff[j] = str[j];
	buff[j] = '\0';
	return (buff);
}

/**
 * _strcpy - Copy a string from source to destination.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcpy(char *dest, const char *src)
{
	char *dest_copy = dest;
	int i;

	for (i = 0; (dest[i] = src[i]); i++)
		;

	return (dest_copy);
}

/**
 * _strcat - Concatenate two strings.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, const char *src)
{
	char *buf = dest;
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; (dest[i] = src[j]) != '\0'; i++, j++)
		;

	return (buf);
}

/**
 * _strncmp - Compare at most n characters of two strings.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 * @n: Number of characters to compare.
 *
 * Return: 0 if strings are equal for
 *the first n characters, negative if s1 < s2,
 *         and positive if s1 > s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	int i, j;

	for (i = 0, j = 0; n > 0 && s1[i] && s1[i] == s2[j]; i++, j++, n--)
		;

	if (n == 0)
	{
		return (0);
	}

	return (*(unsigned char *)&s1[i] - *(unsigned char *)&s2[j]);
}
