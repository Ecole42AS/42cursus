#include "stdio.h"
#include "ctype.h"
#include "string.h"

#include "libft.h"

static char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = strlen(s1);
	while (s2[i] && i < n)
	{
		s1[i + j] = s2[i];
		i++;
	}
	s1[i + j] = '\0';
	return (s1);
}

// #include <stdio.h>

// char	*ft_strncat(char *dest, char *src, unsigned int nb)
// {
// 	unsigned int	i;
// 	unsigned int	j;

// 	i = 0;
// 	j = 0;
// 	while (dest[i] != '\0')
// 	{
// 		i++;
// 	}
// 	while (j < nb && src[j] != '\0')
// 	{
// 		dest[i + j] = src [j];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// 	return (dest);
// }

int	main()
{
	char src[] = "Network";
	char dest[] = "42 ";
	printf("%s", ft_strncat(dest, src, 7));
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*newchain;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	if (len <= 0 || (start + 1 > strlen(s)))
// 	{
// 		newchain = (char *)malloc(1);
// 		*newchain = 0;
// 		return (newchain);
// 	}
// 	newchain = (char *)malloc (sizeof(char) * (len + 1));
// 	if (!newchain)
// 		return (NULL);
// 	i = 0;
// 	if (start < strlen(s))
// 	{
// 		while (s[start] != '\0' && i < len)
// 		{
// 			newchain[i] = s[start];
// 			start++;
// 			i++;
// 		}
// 	}
// 	newchain[i] = '\0';
// 	return (newchain);
// }

// int main()
// {
// 	char str1[] = "Network";
// 	char str2[] = "42 ";

// 	printf("%s", ft_strncat(str1, str2, 7));

	// char *str;
	// str = ft_strrchr("helloktlgrew", 79);
	// printf("%s", str);
// 	char str[] = "roh févvméefr";
// 	size_t	n = strlen(str);
// 	size_t	d = strlen(str) * sizeof(char) + 1;

// 	printf("strlen de str : %ld\n", n);
// 	printf("size of str : %ld\n", sizeof(str));
// 	printf("strlen de str fois 1 + 1 : %ld", d);
// }