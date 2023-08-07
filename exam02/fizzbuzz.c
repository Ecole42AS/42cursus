/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:55:23 by astutz            #+#    #+#             */
/*   Updated: 2022/12/09 20:32:45 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
void printnb(int nb)
{
	if (nb > 9)
		printnb(nb / 10);
	write(1, &"0123456789"[nb % 10], 1);
}
void	fizzbuzz()
{
	int nb;
	
	nb = 1;
	while (nb <= 100)
	{
		if(nb % 3 == 0 && nb % 5 == 0)
			write(1, "fizzbuzz", 8);
		else if(nb % 3 == 0)
			write(1, "fizz", 4);
		else if(nb % 5 == 0)
			write(1, "buzz", 4);
		else
			printnb(nb);
		write(1, "\n", 1);
		nb++;
	}
}

int main()
{
	fizzbuzz();
}