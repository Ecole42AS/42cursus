/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:11:17 by astutz            #+#    #+#             */
/*   Updated: 2023/08/22 14:26:56 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

char	  *get_next_line(int fd)
{
	static char *stash;
	
	if (!BUFFER_SIZE || fd < 0 || (read(fd, 0, 0) < 0))
	{
		
		free(stash);
		stash = NULL;
		return (NULL);
	}
	
	fd = read(fd, stash, BUFFER_SIZE);
}