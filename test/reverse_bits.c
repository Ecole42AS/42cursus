/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:04:59 by astutz            #+#    #+#             */
/*   Updated: 2022/12/19 16:00:53 by astutz           ###   ########.fr       */
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
		res = res * 2 + (octet % 2); //00110010
		octet = octet / 2; 
	}
	return (res);//= 19
}

int main()
{

    int chr = 76;
    unsigned char i = chr;
    unsigned char a;
	a = reverse_bits(i);
    printf("unsigned char: %c\n", a);
	

    return 0;
}