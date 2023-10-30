/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:42:10 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/11/29 11:42:22 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	**ft_split(char *str, char charset);
void	f_memset(char *str, int c, int n);
void	*ft_calloc(size_t el, size_t size);
char	*get_next_line(int fd);
void	grandchild(int fd[2], int gen, char **argv);
void	checks(int argc, char **argv);
void	exec_fail(int temp, char *str, char **args);
void	in_out(int in[2], int out[2], int file_in_out, char *argv);
int		ft_strlen(const char *str);

#endif
