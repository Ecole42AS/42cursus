#include "stdio.h"
#include "ctype.h"
#include "string.h"

#include "libft.h"


void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
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

// int	main()
// {
// 	char src[] = "Network";
// 	char dest[] = "42 ";
// 	printf("%s", ft_strncat(dest, src, 7));
// }


// ***********SUBSTR***********
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

// *******STRTRIM***********
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newchain;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	printf("%d\n", *s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	end = strlen(s1);
	while (end && ft_strchr(set, s1[end]))
	{
		end--;
	}
	newchain = ft_substr ((char *)s1, 0, end + 1 );
	return (newchain);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}


#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newchain;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	newchain = (char *)malloc(sizeof(*s) * strlen(s) + 1);
	if (!newchain)
		return (NULL);
	while (s[i])
	{
		newchain[i] = f(i, s[i]);
		i++;
	}
	newchain[i] = '\0';
	return (newchain);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else if (n < 10)
		ft_putchar_fd((char)(n + '0'), fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}

int	count_words (char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (!s)
		return (0);
	if (s[i] != c)
	{
		i++;
		words++;
	}
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words);
}

char	*make_string(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc (sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		num_words;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	num_words = count_words(s, c);
	result = (char **)malloc (sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			result[i] = make_string (s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	printf("%s", dst);
	return (strlen(src));
}

int main()
{
	// char **str;
	// char str1[] = "hello,world,hello";
	char str1[] = "hel";
	char str2[] = "halr";

	size_t size;
	size = ft_strlcpy(str1, str2, 1);
	// str = ft_split(str1, ',');
	// printf("%s", str[1]);
	printf("%ld\n", size);
	printf("%s", str1);
	// char str2[] = "hello ";

	// printf("%s", ft_strmapi(str1, ft_strchr(str2, 2)));	
	// ft_putnbr_fd(n, 1)
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