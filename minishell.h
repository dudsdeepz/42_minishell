/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:47 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/05 11:53:00 by eduarodr         ###   ########.fr       */
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
# include "./parsing/parsing.h"

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define DEFAULT "\033[0m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define BUFFER_SIZE 1024
# define SHELL_ERROR 0

typedef struct s_tokens
{
	char			**envp;
	char			**token;
}	t_tokens;

void		init_shell(void);
int			ft_strcpy(char *dst, char *src);
int			print_pwd(char *av);
void		display_env(char **env);
void		ft_cd(char *av);
void		ft_echo(char **av);
void		handle_signals(int sig);
char		*ft_putstr(char *str, char *color);
char		*get_shell_prompt(char *username, char *pc_name);
void		sig_actions(void);
t_tokens	*tokens(void);
int 		ft_echo_cases(char **av);
void		ft_export(char **av);
void		ft_unset(char **av);
char 		*ft_strremove(char *substr) ;
char 		**dup_matrix(char **src);
void		free_matrix(char **mtx);
void		get_tokens(char *cwd);
void		executor(void);
char		*get_path(char *command, char **env);
void		free_path(char **list);
char		*triple_strjoin(char *s1, char *s2, char *s3);
int			list_size(char **list);
void		exec_system_cmd(char **tokens, char **env);
int			get_words(char *cwd);
#endif