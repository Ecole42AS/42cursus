/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:17:15 by astutz            #+#    #+#             */
/*   Updated: 2023/10/06 08:39:35 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <errno.h>

extern int	g_exit_code;

typedef struct s_parsing
{
	int					infile;
	int					outfile;
	char				*cmd;
	char				type;
	char				*arg;
	char				*name;
	char				*location;
	char				***env_table;
	struct s_parsing	*next;
}						t_pars;

typedef struct s_ends
{
	int		start;
	int		end;
	int		in_squotes;
	char	*env_value;
}			t_ends;

void		init_termios(void);
char		**lexer(char *input, t_pars *parsing);
void		initialize_parsing(t_pars *my_pars, char ***env_table);
void		parser(char **words, t_pars *parsing);
void		print_linked_list(t_pars *head);
void		signals_init(void (*signals_handle)(int));
void		signals_handle_input(int sig);
void		signals_handle_execution(int sig);
int			is_sp(char *str);
char		*get_first_arg(char *arg, t_pars *token);
int			ft_isnumeric(char *arg);
void		ft_exit(t_pars *token);
void		handle_heredoc(const char *delimiter, t_pars *parsing);
char		*replace_env_var(char *input, t_pars *parsing);
extern void	rl_replace_line(const char *foo, int bar);
extern void	rl_clear_history(void);
char		*remove_quotes(char *input);
void		remove_heredoc(void);
void		display_line(char *input);
int			quotes(char *input, int *i, t_ends *ends, int quote);
char		*append_str(char *str1, char *str2);
char		**append_lines(char **table, char **str, int n);
void		extract_cmd_location(int fd[2], char *name);
char		*extract_prg_name(char *location);
char		*get_next_line(int fd);
void		pipes(t_pars *block);
char		*extract_built_location(char *name);
int			cd(t_pars *block, char **args);
void		commander(t_pars *block);
char		**argumenter(t_pars *block);
char		**init_env(char **env);
void		env(char **env_table);
void		export(char ***env_table, char **argv);
int			unset(char ***env_table, char **argv);
int			max(int a, int b);
char		*bfr_aftr_eq(char *str, int spot, int max_len);
void		del_env(char ***env_table);
int			comp_bfr_eq(char *str1, char *str2);
char		*ft_get_env(char *str, char ***env_table);
void		echo(char **argv);
void		pwd( void );
char		**new_matrix(char **old, int size_change);
void		first_gen(t_pars *block, int fd[2]);
void		mid_gen(t_pars *block, int fgc[2], int fd[2]);
void		last_gen(t_pars *block, int fd[2]);
void		ft_strcpy(char *str1, char *str2);
int			block_type_b(t_pars *block);
int			use_pipe(t_pars *block);
void		*ft_malloc_failed_msg(int size, size_t type);
int			check_pipes_error(char *input);
void		custom_del(void *content);
void		ft_parsclear(t_pars *pars, void (*del)(void*));
void		ft_infile_stuck(char **words, t_pars *parsing, int *i,
				int *is_cmd_or_prog);
void		ft_infile(char **words, t_pars *parsing, int *i,
				int *is_cmd_or_prog);
void		ft_outfile_stuck(char **words, t_pars *parsing, int *i);
void		ft_outfile(char **words, t_pars *parsing, int *i);
void		ft_dinfile_stuck(char **words, t_pars *parsing, int *i);
void		ft_dinfile(char **words, t_pars *parsing, int *i);
void		ft_doutfile_stuck(char **words, t_pars *parsing, int *i);
void		ft_doutfile(char **words, t_pars *parsing, int *i);
void		print_linked_list(t_pars *head);
void		ft_pipe(char **words, t_pars *parsing, int *i);
void		ft_command_or_builtin(char **words, t_pars *parsing,
				int *i, int *is_cmd_or_prog);
void		ft_prog(char **words, t_pars *parsing, int *i, int *is_cmd_or_prog);
void		ft_arg(char **words, t_pars *parsing, int *i);
char		*replace_exit_code(char *input, int *i, int *new_len);
char		*replace_env_value(char *result, t_pars *parsing,
				int *new_len, int *i);
char		*replace_env_value_bis(char *result, int *new_len,
				int *i, t_ends *len);
void		exit_msg(t_pars *token);
int			loop(t_ends *ends, int *i, char *input);
int			quotes(char *input, int *i, t_ends *ends, int quote);
void		waiting(void);

#endif
