/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:04:59 by astutz            #+#    #+#             */
/*   Updated: 2022/12/16 18:19:41 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{
	int i;
	unsigned char res;

	res = 0;
	i = 8;
	while(i--)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
	}
	return (res);
}

int main()
{

    int chr = 76; //L = 2 in reverse bit 01001100
									   //10110011 = 179 = puissance 3 
    unsigned char i = chr;
    unsigned char a;
	a = reverse_bits(i);
    printf("unsigned char: %c\n", a);
	

    return 0;
}