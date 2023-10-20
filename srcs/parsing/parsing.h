/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:38 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/19 14:40:29 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../minishell.h"

typedef struct s_tokens
{
	char	**token;
	int		token_id;
	int 	token_fork;
	struct s_tokens	*next;
}			t_tokens ;

typedef struct s_parser
{
	char			**envp;
	int				tokens_n;
	t_tokens		*tokens;
	int				exit_status;
}	t_parser;

char 	*get_prompt(char *av, char *newav);
int		check_cmds(char **linei);
int		parsing(char *av);
int 	parse_tokens(char *av, char *newav, int *j, int *i);
int 	parse_tokens2(char **av, int *i);
void	print_dp(char **str);
int		tokens_num(char *cwd);
void	clear_tokens(t_tokens **lst, void (*del)(void*));

#endif