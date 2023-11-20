/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:52:57 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/20 18:24:38 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **linei)
{
	if (linei[1])
	{
		if (check_exit_str(linei[1]))
		{
			free_envs();
			printf("exit\nexit: %s: numeric argument required.\n", linei[1]);
			exit(2) ;
		}
		else
		{
			free_envs();
			exit(ft_atoi(linei[1]));
		}
	}
	else
		exit(0);
}

int check_exit_str(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
