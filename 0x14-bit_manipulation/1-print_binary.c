#include "main.h"

/**
 * print_binary - prints the binary equivalent of a decimal number
 * @n: number to print in binary
 */
void print_binary(unsigned long int n)
{
	int i, tally = 0;
	unsigned long int NOS;

	for (i = 63; i >= 0; i--)
	{
		NOS = n >> i;

		if (NOS & 1)
		{
			_putchar('1');
			tally++;
		}
		else if (tally)
			_putchar('0');
	}
	if (!tally)
		_putchar('0');
}

