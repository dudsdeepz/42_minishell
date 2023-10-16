/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:39:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/16 16:34:42 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int parse_tokens(char *av, char *newav, int *j, int *i)
{
	if (av[(*i) + 1] == '|')
		newav[(*j)++] = '\2';
	else if (av[(*i)] == '|')
		newav[(*j)++] = '\2';
	else if (av[*i] == '>' && av[(*i) + 1] == '>')
	{
		newav[(*j)++] = av[*i];
		newav[(*j)++] = '\2';
		(*i)++;
	}
	else if (av[*i] == '<' && av[(*i) + 1] == '<')
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


int	check_cmds(char **linei)
{
	if (!ft_strncmp(linei[0], "pwd", 4))
		print_pwd(*linei);
	else if (!ft_strncmp(linei[0], "exit", 5))
	{
		if (linei[1])
			exit(ft_atoi(linei[1]));
		else
			exit(0);
	}
	else if (!ft_strncmp(linei[0], "env", 4) && !linei[1])
		display_env(parser()->envp);
	else if (!ft_strncmp(linei[0], "cd", 3))
		ft_cd(linei[1]);
	else if (!ft_strncmp(linei[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(linei[0], "export", 7))
		ft_export(linei);
	else if (!ft_strncmp(linei[0], "unset", 6))
		ft_unset(linei);
	else
		return (0);
	return (1);
}