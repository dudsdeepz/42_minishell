/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:38 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/17 00:30:48 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../minishell.h"

typedef struct s_heredoc
{
	char	*h_content;
	int		in_heredoc;
	char	*line;
}			t_heredoc;

typedef struct s_redirect
{
	int		input_red;
	int		output_red;
	int		m_args;
}		 	t_redirect;

typedef struct s_tokens
{	
	char	*sign;
	int		is_file;
	char	**token;
	int		fd[2];
	int		master_error[2];
	int		fd_master[2];
	int		token_fork;
	int		file;
	char	*path;
	int		op;
	pid_t	proc;
	struct s_tokens *prev;
	struct s_tokens *next;
}			t_tokens ;

typedef struct s_parser
{
	char			**export_env;
	char			**tmp_matrix;
	char			**envp;
	int				tokens_n;
	t_heredoc		*heredoc;
	t_tokens		*tokens;
	int				exit_status;
}	t_parser;

char	*get_prompt(char *av, char *newav);
int		exec_cmds(char **linei);
int		parsing(char *av);
int 	parse_tokens(char *av, char *newav, int *j, int *i);
int		parse_tokens2(char **av, int *i);
void	print_dp(char **str);
int		tokens_num(char *cwd);
void	clear_tokens(t_tokens **lst, void (*del)(void*));
int		options(char *signs);
void	fukyu(t_tokens *tokens);
void	one_command(t_tokens *token);
void 	init_lists(char *av, t_tokens **tokens);
int		check_built(char **linei);

#endif