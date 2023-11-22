/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:47 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 10:06:56 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./srcs/parsing/parsing.h"
# include "./srcs/expansion/expansion.h"
# include "./srcs/executor/executor.h"
# include "./srcs/builtins/builtins.h"

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define DEFAULT "\033[0m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define BUFFER_SIZE 1024
# define SHELL_ERROR 0

void		init_shell(void);
void		handle_signals(int sig);
char		*ft_putstr(char *str, char *color);
char		*get_shell_prompt(char *username, char *pc_name);
void		sig_actions(void);
t_parser	*parser(void);
char		**dup_matrix(char **src);
void		free_matrix(char **mtx);
int			shell_output(char *av);
char		*get_path(char *command, char **env);
char		*triple_strjoin(char *s1, char *s2, char *s3);
int			list_size(char **list);
void		shell(char *cwd);
char		*ft_subtokens(char const *s, unsigned int start, size_t len);
void		free_envs(void);
int         ft_heredoc(char *a);
void		free_tokens(t_tokens **tokens);
int	        ft_strcmp(char *s1, char *s2);
void		alloc_tokens(t_tokens **tokens);

#endif