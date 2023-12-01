/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:28:15 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 11:32:58 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	help_me(char *token)
{
	char	**tmp;

	tmp = NULL;
	tmp = send_to_exportenv(token, parser()->export_env);
	parser()->export_env = tmp;
}

static void	help_me2(char *token)
{
	export_util(token);
}

void	display_export(char **env)
{
	int	i;
	int	a;
	int	checker;

	i = 0;
	while (env[i])
	{
		a = 0;
		checker = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][a])
		{
			write(1, &env[i][a++], 1);
			if (!checker && env[i][a - 1] == '=')
			{
				write(1, "\"", 1);
				checker++;
			}
		}
		if (checker)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
	return ;
}

void	_ft_export(t_tokens **token)
{
	int		i;

	i = 0;
	if ((*token)->token[1])
	{
		while ((*token)->token[++i])
		{
			if (check_export_str((*token)->token[i]))
			{
				parser()->exit_status = 1;
				ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
				continue ;
			}
			if (!difs((*token)->token[i], '='))
				help_me2((*token)->token[i]);
			else
				help_me((*token)->token[i]);
			parser()->exit_status = 0;
		}
	}
	else
		display_export(parser()->export_env);
	return ;
}

int	check_export_str(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || !ft_isalpha(str[i]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}
