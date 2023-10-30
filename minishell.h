/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:47 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/30 11:27:22 by eduarodr         ###   ########.fr       */
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
int			ft_strcpy(char *dst, char *src);
void		handle_signals(int sig);
char		*ft_putstr(char *str, char *color);
char		*get_shell_prompt(char *username, char *pc_name);
void		sig_actions(void);
t_parser	*parser(void);
char 		*ft_strremove(char *substr) ;
char 		**dup_matrix(char **src);
void		free_matrix(char **mtx);
void		get_tokens(char *av);
char		*get_path(char *command, char **env);
void		free_path(char **list);
char		*triple_strjoin(char *s1, char *s2, char *s3);
int			list_size(char **list);
void		exec_system_cmd(char **tokens, char **env, int tkid);
void 		shell(char *cwd);
void		free_heredoc(char *heredoc_content);
char		*ft_strcat(char *dest, char *src);
size_t		ft_strcspn(const char *s, const char *reject);
char		**get_signs(char *token);
char		*ft_subtokens(char const *s, unsigned int start, size_t len);

#endif