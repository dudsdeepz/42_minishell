/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:08:34 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/13 11:52:37 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **av)
{
	int	i;

	i = 0;
	if (av[i + 1])
	{
		if (!ft_strncmp(av[i + 1], "-n", 2))
			n_case(av);
		else
		{
			while (av[++i])
			{				
				ft_putstr_fd(av[i], STDOUT_FILENO);
				ft_putstr_fd(" ", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void n_case(char **av)
{
	int i;
	int a;

	i = 2;
	a = 0;
	while (av[i])
	{
		while (av[i][a])
		{
			if (av[i][a] == '\n')
				a++;
			ft_putchar_fd(av[i][a], STDOUT_FILENO);
			a++;
		}
		i++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}
