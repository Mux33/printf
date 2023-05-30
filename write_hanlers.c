#include "main.h"
/**
*  * handle_write_char - a function that prints a string
*   * @c: character string
*    * @buffer: a buffer that carries characters
*     * @flags: checks for flags
*      * @width: checks for width
*       * @precision: checks for precision
*        * @size: checks for size
*         * Return: characters rinted
*/

int handle_write_char(char c, char buffer[], int flags,
int width, int precision, int size)
{
int i = 0;
char padd = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padd = '0';

buffer[i++] = c;
buffer[i] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (i = 0; (width - 1) > 1; i++)
buffer[BUFF_SIZE - i - 2] = padd;

if (flags & F_MINUS)
return (write(1, &buffer[0], 1) +
write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
write(1, &buffer[0], 1));
}
return (write(1, &buffer[0], 1));
}

/* writes number */
/**
*  * write_number - function that prints a number
*   * @is_negative: checks for -ve numbers
*    * @ind: character types
*     * @buffer: holds values
*      * @flags: checks for flags
*       * @width: checks for width
*        * @precision: checks for precision
*         * @size: checks for size
*          * Return: VAlues printed
*/
int write_number(int is_negative, int ind, char buffer[], int flags,
int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;

UNUSED(size);

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';

return (write_num(ind, buffer, flags,
width, precision, length, padd, extra_ch));
}
/**
*  * write_num - function that writes a number
*   * @ind: index of 1st element in the buffer
*    * @buffer: holds the values
*     * @flags: checks for flags
*      * @width: checks the width
*       * @prec: Checks the precision
*        * @length: checks length
*         * @padd: spaces at the edges
*          * @extra_c: te ectra character
*           * Return: Printed Values
*/
int write_num(int ind, char buffer[], int flags,
int width, int prec,
int length, char padd, char extra_c)
{
int i, padd_start = 1;

if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0);
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padd = ' ';
if (prec > 0 && prec < length)
padd = ' ';
while (prec > length)
buffer[--ind] = '0', length++;
if (extra_c != 0)
length++;
if (width > length)
{
for (i = 1; i < width - length + 1; i++)
buffer[i] = padd;
buffer[i] = '\0';
if (flags & F_MINUS && padd == ' ')
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
}
else if (!(flags & F_MINUS) && padd == ' ')
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')
{
if (extra_c)
buffer[--padd_start] = extra_c;
return (write(1, &buffer[padd_start], i - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start)));
}
}
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length));
}
/**
*  * write_unsgnd - prints unsigned numbrs
*   * @is_negative: showing -ve numbers
*    * @ind: ist element in buffer
*     * @buffer: hold numbers
*      * @flags: checks for flags
*       * @width: checks width
*        * @precision: Checks for precision
*         * @size: checks size
*          * Return: printed numbers
*/
int write_unsgnd(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length;
int i;
char padd = ' ';

i = 0;
length = BUFF_SIZE - ind - 1;

UNUSED(is_negative);
UNUSED(size);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0);
if (precision > 0 && precision < length)
padd = ' ';
while (precision > length)
{
buffer[--ind] = '0';
length++;
}
if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (width > length)
{
for (i = 0; i < width - length; i++)
buffer[i] = padd;
buffer[i] = '\0';

if (flags & F_MINUS)
{
return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
}
else
{
return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
}
}
return (write(1, &buffer[ind], length));
}
/**
*  * write_pointer - function that writes address
*   * @buffer: holds characters
*    * @ind: 1st member of what is in buffer
*     * @length: length
*      * @width: checks width
*       * @flags: checks for flags
*        * @padd: space on both sides
*         * @extra_c: character
* @padd_start: where padding to start
*Return: printed numbrs
*/
int write_pointer(char buffer[],
int ind, int length,
int width, int flags, char padd, char extra_c, int padd_start)
{
int i;

if (width > length)
{
for (i = 3; i < width - length + 3; i++)
buffer[i] = padd;
buffer[i] = '\0';
if (flags & F_MINUS && padd == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
}
else if (!(flags & F_MINUS) && padd == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')
{
if (extra_c)
buffer[--padd_start] = extra_c;
buffer[1] = '0';
buffer[2] = 'x';
return (write(1, &buffer[padd_start], i - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start) - 2));
}
}
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
