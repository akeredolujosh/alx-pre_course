#include "shell.h"

/**
* interactive - A function.
*
* It takes a parameter named info,
*
* which is of type struct address.
*
* The function returns 1 if the shell is currently in interactive mode,
*
* and 0 otherwise.
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim. The function takes two parameters,
*
* a character named @c and a string named @delim.
*
* The purpose of the function is to determine
*
* if the input character is a delimiter or not
*
* by comparing it to the provided delimiter string.
*
* If the character is a delimiter,
*
* the function returns 1, otherwise, it returns 0.
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
* _isalpha is a function use to determine whether the input character
*
* @c is an alphabetic character or not.
*
* If the input character is alphabetic,
*
* the function returns 1. Otherwise, it returns 0.
*/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
* _atoi - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
* This function takes a string argument
* and converts it to an integer. The string
* must consist of digits, optionally preceded
* by a '+' or '-' sign. The function
* returns 0 if there are no digits in the string.
* If there are digits, it returns
* the converted integer with the appropriate sign.
*/

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
