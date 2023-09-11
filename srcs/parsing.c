/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:21:13 by eduarodr          #+#    #+#             */
/*   Updated: 2023/09/11 15:30:32 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_parsing(char **av)
{
	int		i;

	i = 0;
    tokens()->is_file = 0;
    tokens()->is_argument = 0;
	while (av[i])
	{
		if (check_cmds(av[i]))
			i++;
		else if (check_pipes(av[i]))
			i++;
		else if (tokens()->is_file || tokens()->is_argument)
       {
			i++;
            tokens()->is_file = 0;
        }
		else if (tokens()->is_argument)
		{
			while ((ft_strncmp(av[i], ">", 2) || ft_strncmp(av[i], "|", 2)) && i++)
				ft_strjoin(av[i], av[i + 1]);
		}
		else
			return(printf("minishell: command not found: %s\n", av[i]));
	}
	return (0);
}

int	check_pipes(char *linei)
{
	if (!ft_strncmp(linei, "<", 2))
		return(1);
	else if (!ft_strncmp(linei, ">", 2))
	{
		tokens()->is_file = 1;
		return (1);
	}
	else if (!ft_strncmp(linei, "|", 2))
		return (1);
	else if (!ft_strncmp(linei, "$", 2))
		return (1);
	return (0);
}

int	check_cmds(char *linei)
{
	if (!ft_strncmp(linei, "pwd", 4))
		return (1);
	else if (!ft_strncmp(linei, "clear", 6) && !linei + 1)
		return (1);
	else if (!ft_strncmp(linei, "exit", 5))
		return (1);
	else if (!ft_strncmp(linei, "env", 4) && !linei + 1)
		return (1);
	else if (!ft_strncmp(linei, "cd", 3))
		tokens()->is_argument = 1;
	else if (!ft_strncmp(linei, "echo", 5))
		tokens()->is_argument = 1;
	else if (!ft_strncmp(linei, "export", 7))
		tokens()->is_argument = 1;
	else if (!ft_strncmp(linei, "unset", 6))
		tokens()->is_argument = 1;
	else
		return (0);
	return (1);
}
