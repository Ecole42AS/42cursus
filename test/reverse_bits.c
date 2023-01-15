/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:04:59 by astutz            #+#    #+#             */
/*   Updated: 2023/01/15 11:54:24 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet) // "2" --> ascii = 50
{
	int i;
	unsigned char res;

	res = 0;
	i = 8;
	while(i--)
	{
		res = res * 2 + (octet % 2); // 1, 2, 5, 11, 22, 44, 88, 176
		octet = octet / 2; // 13, 6(1), 3, 1(1), 0(1)
	}
	return (res);//= 19
}

void printbits(unsigned char octet)
{
	unsigned char bit;
	int i;
	
	i = 8;
	while (i--)
	{
		bit = (octet >> i & 1) + 48;
		write(1, &bit, 1);
	}
}

int main()
{

    int chr = 13;
    unsigned char i = chr;
    unsigned char a;
	printbits(i);
    printf("\n");
	a = reverse_bits(i);
	printbits(a);
    printf("\nunsigned char: %d\n", a);
	

    return 0;
}

// int main()
// {
// 	unsigned char c;

// 	c = 87;
// 	printf("unsigned char: %c\n", c);
	
// }

