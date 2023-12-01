/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:52:57 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 15:18:37 by eduarodr         ###   ########.fr       */
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
	free_all();
	exit(tmp);
}

static void	cd_aux(void)
{
	ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
}

void	_ft_exit(t_tokens **token)
{
	close_fds(token, 0);
	if ((*token)->token[1])
	{
		if (check_exit_str((*token)->token[1]))
		{
			cd_aux();
			free_all();
			exit(2);
		}
		else if ((*token)->token[2])
		{
			parser()->exit_status = 1;
			ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		}
		else
			exit_aux((*token)->token[1]);
	}
	else
	{
		printf("exit\n");
		free_all();
		close(1);
		exit(parser()->exit_status);
	}
}

int	check_exit_str(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 18)
		return (1);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+' || str[i] == '#')
			i++;
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_all(void)
{
	free_envs();
	clear_history();
	if (parser()->head_token)
		free_tokens(parser()->head_token);
	if (parser()->splited)
		free_matrix(parser()->splited);
	if (parser()->newav)
		free(parser()->newav);
}
