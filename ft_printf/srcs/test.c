#include <stdio.h>

void	ft_putptr_fd(void *ptr, int fd)
{
	write(1, &ptr, 5);//test
	//ft_putstr_fd((void *)ptr, fd);
}

int main()
{
	unsigned int a = -1;
	unsigned int b = -2;
	unsigned int c = -3;
	char *ptr = "Hello";
	char *ptr2 = ((char *)ft_putptr_fd(ptr, 1));
	
	printf("%p", ptr2);
	printf("\na: %u\n", a);
	printf("b: %u\n", b);
	printf("c: %u\n", c);
}