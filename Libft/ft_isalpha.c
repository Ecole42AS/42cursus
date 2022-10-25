#include "libft.h"
// #include "stdio.h"

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// int main()
// {
//   int res = ft_isalpha(65);
//   printf("%d", res);
// }