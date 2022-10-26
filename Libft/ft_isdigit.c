

#include "libft.h"
#include "stdio.h"

int ft_isdigit(int n)
{
    if(n >= 0 && n <= 9)
        return 1;
    return 0;
}

// int main()
// {
//   int res = ft_isdigit(9);
//   printf("%d", res);
// }