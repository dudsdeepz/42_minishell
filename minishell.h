/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:47 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 14:54:10 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <termios.h>
# include <errno.h>
# include <stdlib.h>
# include <sgtty.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./srcs/parsing/parsing.h"
# include "./srcs/expansion/expansion.h"
# include "./srcs/executor/executor.h"
# include "./srcs/builtins/builtins.h"
# include "./srcs/gnl/get_next_line.h"

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define DEFAULT "\033[0m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define BUFFER_SIZE 10
# define SHELL_ERROR 0

void		init_shell(void);
void		handle_signals(int sig);
char		*ft_putstr(char *str, char *color);
char		*get_shell_prompt(char *username, char *pc_name);
void		sig_actions(void);
t_parser	*parser(void);
char		**dup_matrix(char **src);
void		free_matrix(char **mtx);
int			shell_output(char *av, char **splited);
char		*get_path(char *command, char **env);
char		*triple_strjoin(char *s1, char *s2, char *s3);
int			list_size(char **list);
void		shell(char *cwd);
char		*ft_subtokens(char const *s, unsigned int start, size_t len);
void		free_envs(void);
int			ft_heredoc(char *a);
void		free_tokens(t_tokens *token);
int			ft_strcmp(char *s1, char *s2);
void		alloc_tokens(t_tokens **tokens);
void		hd_loop(char *str, int *fd, int flag);
void		hd_signs(int sig);
void		term_change(void);
int			heredoc_error(char *str);
int			path_helper(char **env, int *i);
void		free_str_h(char *str, char *command);
int			free_path_helper(char *str, char *command, char **path);
char		**prep_str(char **str);
void		go_top(t_tokens **lst);
void		handle_signals2(int sig);
void		shell_aux(char **env);
void		aux_shelloutput(t_tokens *token);
void		aux_vars(void);
void		builtins_close(t_tokens *tokens);
char		*file_quotes(char *str);
void		create_pipes(t_tokens *tokens);
void		free_all(void);
void		free_all_hd(void);
void		free_aux(char *cwd);

#endif
