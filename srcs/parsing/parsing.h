/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:38 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/21 15:34:20 by eduarodr         ###   ########.fr       */
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
	void	(*_exec_cmd)(struct s_tokens **tokens);
	int		token_size;
	char	**token;
	int		fd[2];
	int		master_error[2];
	int		fd_master[2];
	char	*path;
	struct s_tokens *prev;
	struct s_tokens *next;
}			t_tokens ;

typedef struct s_parser
{
	int				global_error;
	char			**export_env;
	char			**tmp_matrix;
	char			**envp;
	int				tokens_n;
	t_heredoc		*heredoc;
	t_tokens		*tokens;
	int				exit_status;
}	t_parser;

char	*get_prompt(char *av, char *newav);
int		parsing(char *av);
int 	parse_tokens(char *av, char *newav, int *j, int *i);
int		parse_tokens2(char **av, int *i);
void	print_dp(char **str);
int		tokens_num(char **cwd);
int		options(char *str);
void	one_command(t_tokens *token);
t_tokens *init_lists(char **av, t_tokens *token);
int		check_built(char **linei);
void	get_tokens_size(char **splited, t_tokens **tokens);
void	alocate_tokens(t_tokens **tokens);
int		is_sign(char *sign);
int		separeites_tokens(t_tokens **tokens, char **splited);
int		full_check_dq(char **splited);

#endif