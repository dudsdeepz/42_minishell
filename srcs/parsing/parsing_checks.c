/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:39:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/05 16:33:10 by eduarodr         ###   ########.fr       */
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


int	check_cmds(char *linei)
{
	char	**args;

	args = ft_split(linei, '\2');
	if (!ft_strncmp(args[0], "pwd", 4))
		print_pwd(linei);
	else if (!ft_strncmp(args[0], "exit", 5))
	{
		if (args[1])
			exit(ft_atoi(args[1]));
		else
			exit(0);
	}
	else if (!ft_strncmp(args[0], "env", 4) && !args[1])
		display_env(tokens()->envp);
	else if (!ft_strncmp(args[0], "cd", 3))
		ft_cd(args[1]);
	else if (!ft_strncmp(args[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(args[0], "export", 7))
		return (1);
	else if (!ft_strncmp(args[0], "unset", 6))
		return (1);
	else
		return (0);
	return (1);
}