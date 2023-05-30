#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @j: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *j)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int a, curr_j;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_j = *j + 1; format[curr_j] != '\0'; curr_j++)
	{
		for (a = 0; FLAGS_CH[curr_j] != '\0'; a++)
			if (format[curr_j] == FLAGS_CH[a])
			{
				flags |= FLAGS_ARR[a];
				break;
			}

		if (FLAGS_CH[a] == 0)
			break;
	}

	*j = curr_j - 1;

	return (flags);
}

