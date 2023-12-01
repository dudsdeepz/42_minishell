/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:38 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 12:39:07 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../minishell.h"

typedef struct s_redirect
{
	int		input_red;
	int		output_red;
	int		m_args;
}			t_redirect;

typedef struct s_tokens
{
	void			(*_exec_cmd)(struct s_tokens **tokens);
	int				token_size;
	char			**token;
	int				fd[2];
	int				fd_redir[2];
	char			*path;
	struct s_tokens	*prev;
	struct s_tokens	*next;
	int				error;
}			t_tokens;

typedef struct s_parser
{
	int				pas_exp;
	char			*exp_var;
	char			**export_env;
	char			**tmp_matrix;
	char			*tmp_var;
	char			*tmp_var2;
	char			**envp;
	char			**splited;
	t_tokens		*head_token;
	int				exit_status;
	int				hd;
	int				pause;
	struct termios	termios_save;
	char			*free_stts;
	char			*hd_free;
	char			**hd_free_2;
	char			*was_redir;
	int				hd_fd[2];
	char			*free_pas_ex;
	int				list_size;
	char			*newav;
}					t_parser;

char		*get_prompt(char *av, char *newav);
int			parsing(char *av);
int			parse_tokens(char *av, char *newav, int *j, int *i);
int			parse_tokens2(char **av, int *i);
void		print_dp(char **str);
int			tokens_num(char **cwd);
int			options(char *str);
t_tokens	*init_lists(char **av, t_tokens *tokens);
int			check_built(char **linei);
void		get_tokens_size(char **splited, t_tokens **tokens);
void		alocate_tokens(t_tokens **tokens);
int			is_sign(char *sign);
t_tokens	*separeites_tokens(t_tokens **tokens, char **splited);
int			full_check_dq(char **splited);
char		*get_status(char *str, int i, char *val);

#endif