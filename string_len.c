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
 * Return: A pointer to the newly allocated duplicated string.
 *         NULL if str is NULL or if memory allocation fails.
 */
char *_strdup(char *str)
{
	int len = 0, j = 0;
	char *buff;

	if (!str)
		return (NULL);
	while (str[len] != '\0')
		len++;
	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	while (str[j] != '\0')
	{
		buff[j] = str[j];
		j++;
	}
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
	char *saved_dest = dest;

	while ((*dest++ = *src++))
		;
	return (saved_dest);
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
	char *saved_dest = dest;

	while (*dest != '\0')
		dest++;

	while ((*dest = *src) != '\0')
	{
		dest++;
		src++;
	}

	return (saved_dest);
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
	while (n > 0 && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
