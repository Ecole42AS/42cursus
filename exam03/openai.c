#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void put_string(char *string, int *length) {
    if (!string)
        string = "(null)";
    while (*string)
        *length += write(1, string++, 1);
}

void put_digit(long long int number, int base, int *length) {
    char *hexadecimal = "0123456789abcdef";

    if (number < 0) {
        number *= -1;
        *length += write(1, "-", 1);
    }
    if (number >= base)
        put_digit((number / base), base, length);
    *length += write(1, &hexadecimal[number % base], 1);
}

int ft_printf(const char *format, ...) {
    int length = 0;

    va_list pointer;
    va_start(pointer, format);

    int i = 0; // Variable to iterate through the format string
    while (format[i]) {
        if ((format[i] == '%') && ((format[i + 1] == 's') || (format[i + 1] == 'd') || (format[i + 1] == 'x'))) {
            i++; // Move past the '%'
            if (format[i] == 's')
                put_string(va_arg(pointer, char *), &length);
            else if (format[i] == 'd')
                put_digit((long long int)va_arg(pointer, int), 10, &length);
            else if (format[i] == 'x')
                put_digit((long long int)va_arg(pointer, unsigned int), 16, &length);
        } else
            length += write(1, &format[i], 1);
        i++; // Move to the next character in the format string
    }
    va_end(pointer);
    return length;
}

int main() {
    printf("=== Testing ft_printf ===\n");

    // Test with strings and integers
    ft_printf("Hello, %s!\n", "world");
    ft_printf("The answer is %d.\n", -42);

    // Test with hexadecimal integers
    ft_printf("Hexadecimal: %x\n", -777);
    ft_printf("Hexadecimal: %x\n", 0x1000);

    return 0;
}
