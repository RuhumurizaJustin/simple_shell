#include "simple_shell.h"

/**
 * str_length - length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_length(char *string)
{
	int size = 0;

	if (string == NULL)
		return (0);

	while (string[size++] != '\0')
	{
	}
	return (--size);
}

/**
 * str_duplicate - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *str_duplicate(char *string)
{
	char *result;
	int size, j;

	if (string == NULL)
		return (NULL);

	size = str_length(string) + 1;

	result = malloc(sizeof(char) * size);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (j = 0; j < size; j++)
	{
		result[j] = string[j];
	}

	return (result);
}

/**
 * str_compare - Compare two strings
 * @string1: String one
 * @string2: String two
 * @number: number of characters
 * Return: 1 if the strings are equals
 * 0 if the strings are different
 */
int str_compare(char *string1, char *string2, int number)
{
	int iterator;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (iterator = 0; string1[iterator]; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
	else
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (string1[iterator] != string2[iterator])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concatenates two strings.
 * @string1: String one
 * @string2: String two
 *
 * Return: pointer to the array
 */
char *str_concat(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = str_length(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);

	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}


/**
 * str_reverse - reverses a string.
 * @string: pointer to string.
 * Return: void.
 */
void str_reverse(char *string)
{

	int j = 0, size = str_length(string) - 1;
	char hold;

	while (j < size)
	{
		hold = string[j];
		string[j++] = string[size];
		string[size--] = hold;
	}
}
