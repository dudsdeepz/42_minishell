/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:38 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/05 12:15:07 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"

char 	*get_prompt(char *av, char *newav);
int		check_tokens(char *linei);
int		check_cmds(char *linei);
int 	check_pipe(char *av, char *newav, int *j, int *i);
int		parsing(char *av);
char 	*check_aspas(char *av, char *newav);

#endif