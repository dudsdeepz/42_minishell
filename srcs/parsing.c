/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:21:13 by eduarodr          #+#    #+#             */
/*   Updated: 2023/09/28 17:51:40 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_parsing(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (check_pipes(av[i]))
		{
			if (!av[i + 1] || check_pipes(av[i + 1]) || ft_strlen(av[i]) > 1)
				return(printf("minishell: Syntax error!	\n"));
		}
		++i;	
	}
	return (0);
}

int	check_pipes(char *linei)
{	
	if (!ft_strncmp(linei, "<", 2))
		return(1);
	else if (!ft_strncmp(linei, ">", 2))
		return (1);
	else if (!ft_strncmp(linei, "|", 2))
		return (1);	
	else if (!ft_strncmp(linei, "$", 2))
		return (1);
	return (0);
}

int	check_cmds(char *linei)
{
	char **args;
	
	args = ft_split(linei, ' ');
	if (!ft_strncmp(args[0], "pwd", 4))
		print_pwd(linei);
	else if (!ft_strncmp(args[0], "exit", 5))
	if (args[1])
		exit(ft_atoi(args[1]));
	else
		exit(0);
	else if (!ft_strncmp(args[0], "env", 4) && !args[1])
		display_env(tokens()->envp);
	else if (!ft_strncmp(args[0], "cd", 3))
		ft_cd(args[1]);
	else if (!ft_strncmp(args[0], "echo", 5))
		return 1;
	else if (!ft_strncmp(args[0], "export", 7))
		return 1;
	else if (!ft_strncmp(args[0], "unset", 6))
		return 1;
	else
		return (0);
	return (1);
}
