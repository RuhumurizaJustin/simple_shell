#include "simple_shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: It´s pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int h;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (h = 0; delim[h] != '\0'; h++)
		{
			if (*str == delim[h])
			break;
		}
		if (delim[h] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (h = 0; delim[h] != '\0'; h++)
		{
			if (*str == delim[h])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
