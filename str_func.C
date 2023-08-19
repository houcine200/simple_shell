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


