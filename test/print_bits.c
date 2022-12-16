/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:01:08 by astutz            #+#    #+#             */
/*   Updated: 2022/12/16 18:10:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void print_bits(unsigned char octet)
{
	int	i = 8;  // 0000 1000 quand i = chiffres impaires => 0000 0001
				// 0000 0111
				// 0000 0110
				// 0000 0101
				// 0000 0100
				// 0000 0011
				// 0000 0010
			    // 0000 0001
	unsigned char 	bit;

	while (i--)
	{
		bit = (octet >> i & 1) + '0'; // ca va tjrs marquer 1 ou zero depend du bit final.
		write(1, &bit, 1);
	}
}

int main()
{

    int chr = 126;
    unsigned char i = chr;
	print_bits(i);
    printf("unsigned char: %c\n", i);
	

    return 0;
}