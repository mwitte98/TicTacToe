#include <stddef.h>
#include <stdint.h>

#include "debug.h"

char digit_to_char(char ch)
{
    if (ch < 10)
    {
        return ch + '0';
    }
    else
    {
        return modulo(ch, 10) + 'A';
    }
}

char* convert(uint32_t base, uint32_t numToConvert, char* buffer)
{
    if (numToConvert == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
    }
    else
    {
        size_t i = 0;
        while(numToConvert != 0)
        {
            buffer[i++] = digit_to_char(modulo(numToConvert, base));
            numToConvert = integer_division(numToConvert, base);
        }
        char *start = buffer;
        char *end = start + i - 1;
        char temp;
        while (end > start)
        {
            temp = *start;
            *start = *end;
            *end = temp;

            ++start;
            --end;
        }
        buffer[i] = '\0';
    }

    return buffer;
}

char* to_binary_str(uint32_t numToConvert, char* buffer)
{
    return convert(2, numToConvert, buffer);
}

char* to_hex_str(uint32_t numToConvert, char* buffer)
{
    return convert(16, numToConvert, buffer);
}

char* to_decimal_str(uint32_t numToConvert, char* buffer)
{
    return convert(10, numToConvert, buffer);
}

uint32_t integer_division(uint32_t dividend, uint32_t divisor)
{
    uint32_t i = 0;
	uint32_t counter = dividend;

    while (counter >= divisor)
    {
        i++;
		counter -= divisor;
    }
	
    return i;
}

uint32_t modulo(uint32_t dividend, uint32_t divisor)
{
	uint32_t counter = dividend;

    while (counter >= divisor)
    {
		counter -= divisor;
    }
	
    return counter;
}
