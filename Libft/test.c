#include "stdio.h"
#include "ctype.h"
#include "string.h"

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = strlen((char *)s) + 1;
	while (len--)
	{
		if (s[len] == (char)c)
			return ((char *)&s[len]);
	}
	printf("%p", &s[len]);
	return (NULL);
}

int main()
{
// 	char str[] = "roh févvméefr";
// 	size_t	n = strlen(str);
// 	size_t	d = strlen(str) * sizeof(char) + 1;

// 	printf("strlen de str : %ld\n", n);
// 	printf("size of str : %ld\n", sizeof(str));
// 	printf("strlen de str fois 1 + 1 : %ld", d);
}