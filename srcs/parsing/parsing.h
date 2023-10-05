/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:38 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/05 16:32:13 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../minishell.h"

char 	*get_prompt(char *av, char *newav);
int		check_cmds(char *linei);
int		parsing(char *av);
int 	parse_tokens(char *av, char *newav, int *j, int *i);
int 	parse_tokens2(char **av, int *i);

#endif