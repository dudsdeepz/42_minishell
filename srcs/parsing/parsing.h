/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:38 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/12 16:43:32 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../minishell.h"

typedef struct s_tokens
{
	char	**token;
	int		token_id;
	struct s_tokens	*next;
}			t_tokens ;

typedef struct s_parser
{
	char			**envp;
	int				tokens_n;
	t_tokens		*tokens;
}	t_parser;

char 	*get_prompt(char *av, char *newav);
int		check_cmds(char **linei);
int		parsing(char *av);
int 	parse_tokens(char *av, char *newav, int *j, int *i);
int 	parse_tokens2(char **av, int *i);
void	print_dp(char **str);

#endif