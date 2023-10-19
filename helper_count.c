#include "simple_shell.h"

/**
 * long_to_string - converts a number to a string.
 * @number: number in a string.
 * @string: string input
 * @base: base to convert number
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int position = 0, inNegative = 0;
	long quotient = number;
	char letters[] = {"0123456789abcdef"};

	if (quotient == 0)
		string[position++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (quotient)
	{
		if (quotient < 0)
			string[position++] = letters[-(quotient % base)];
		else
			string[position++] = letters[quotient % base];
		quotient /= base;
	}
	if (inNegative)
		string[position++] = '-';

	string[position] = '\0';
	str_reverse(string);
}


/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to string
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	size_t number = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_characters - count the character in string.
 *
 * @string: pointer to string
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */
int count_characters(char *string, char *character)
{
	int c, counter = 0;

	for (c = 0; string[c]; c++)
	{
		if (string[c] == character[0])
			counter++;
	}
	return (counter);
}
