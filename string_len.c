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
char *_strcpy(char *dest, const char *src) 
{
    char *saved_dest = dest;
    while ((*dest++ = *src++))
        ;
    return saved_dest;
}
