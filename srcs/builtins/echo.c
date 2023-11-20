/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:08:34 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/20 21:25:17 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_ft_echo(t_tokens **token)
{
	int	i;

	i = 0;
	if ((*token)->token[i + 1])
	{
		if (!ft_strncmp((*token)->token[i + 1], "-n", 2))
			n_case((*token)->token);
		else
		{
			while ((*token)->token[++i])
			{				
				ft_putstr_fd((*token)->token[i], STDIN_FILENO);
				if ((*token)->token[i + 1])
					ft_putstr_fd(" ", STDIN_FILENO);
			}
			ft_putstr_fd("\n", STDIN_FILENO);
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
