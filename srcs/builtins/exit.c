/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:52:57 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/30 12:27:34 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exit_aux(char *token)
{
	int	tmp;

	tmp = 0;
	tmp = ft_atoi(token);
	if (tmp > 256)
		tmp %= 256;
	free_envs();
	exit(tmp);
}

void	_ft_exit(t_tokens **token)
{
	if ((*token)->token[1])
	{
		if ((*token)->token[2])
		{
			parser()->exit_status = 1;
			ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		}
		else if (check_exit_str((*token)->token[1]))
		{
			free_envs();
			ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
			exit(2);
		}
		else
			exit_aux((*token)->token[1]);
	}
	else
	{
		close(1);
		close_fds(token, 0);
		exit(parser()->exit_status);
	}
}

int	check_exit_str(char *str)
{
	int	i;

	i = 0;
	if 	(ft_strlen(str) > 18)
		return (1);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
