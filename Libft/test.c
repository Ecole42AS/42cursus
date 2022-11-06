#include "stdio.h"
#include "ctype.h"
#include "string.h"

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newchain;
	size_t	i;

	if (!s)
		return (NULL);
	if (len <= 0 || (start + 1 > strlen(s)))
	{
		newchain = (char *)malloc(1);
		*newchain = 0;
		return (newchain);
	}
	newchain = (char *)malloc (sizeof(char) * (len + 1));
	if (!newchain)
		return (NULL);
	i = 0;
	if (start < strlen(s))
	{
		while (s[start] != '\0' && i < len)
		{
			newchain[i] = s[start];
			start++;
			i++;
		}
	}
	newchain[i] = '\0';
	return (newchain);
}

int main()
{
	char *str;

	str = ft_substr("hello", 4, 0);
	printf("%s", str);
	// char *str;
	// str = ft_strrchr("helloktlgrew", 79);
	// printf("%s", str);
// 	char str[] = "roh févvméefr";
// 	size_t	n = strlen(str);
// 	size_t	d = strlen(str) * sizeof(char) + 1;

// 	printf("strlen de str : %ld\n", n);
// 	printf("size of str : %ld\n", sizeof(str));
// 	printf("strlen de str fois 1 + 1 : %ld", d);
}