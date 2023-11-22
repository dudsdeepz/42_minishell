/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:52:57 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 14:07:43 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_ft_exit(t_tokens **token)
{
	if ((*token)->token[1])
	{
		if (check_exit_str((*token)->token[1]))
		{
			free_envs();
			printf("exit\nexit: %s: numeric argument required.\n", (*token)->token[1]);
			exit(2) ;
		}
		else
		{
			free_envs();
			exit(ft_atoi((*token)->token[1]));
		}
	}
	else
		exit(parser()->exit_status);
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
