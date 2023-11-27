/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:39:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/27 14:09:33 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_tokens(char *av, char *newav, int *j, int *i)
{
	if (av[(*i) + 1] == '|')
		newav[(*j)++] = '\2';
	else if (av[(*i)] == '|')
		newav[(*j)++] = '\2';
	else if (av[*i] == '<' && av[(*i) + 1] == '<')
	{
		newav[(*j)++] = av[*i];
		newav[(*j)++] = '\2';
		(*i)++;
	}
	else if (av[*i] == '>' && av[(*i) + 1] == '>')
	{
		newav[(*j)++] = av[*i];
		newav[(*j)++] = '\2';
		(*i)++;
	}
	else if (av[*i] == '>' || av[*i] == '<')
		newav[(*j)++] = '\2';
	else if (av[(*i) + 1] == '>' || av[(*i) + 1] == '<')
		newav[(*j)++] = '\2';
	return (*j);
}
