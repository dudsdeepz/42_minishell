/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:08:34 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/26 16:09:04 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_n(char token)
{
	if (token == 'n')
		return (1);
	return (0);
}

static void	echo_print(char **str, size_t i)
{
	size_t	j;

	j = 0;
	while (str[j])
		j++;
	while (str[i])
	{
		if ((i + 1) != j)
			printf("%s ", str[i]);
		else
			printf("%s", str[i]);
		i++;
	}
}

void	_ft_echo(t_tokens **token)
{
	int	flag;
	
	flag = 0;
	if ((*token)->token[1] && (*token)->token[1][0] \
		== '-' && (*token)->token[1][1] == 'n')
		n_case(token, &flag);
	if (flag == 1 || !flag)
	{
		echo_print((*token)->token, 1);
		printf("\n");
	}
	else if (flag == 2)
		echo_print((*token)->token, 2);
	close_fds(token, 0);
}

void	n_case(t_tokens **token, int *flag)
{
	int	i;

	i = 1;
	while ((*token)->token[1][i])
	{
		if (!(valid_n((*token)->token[1][i])))
		{
			(*flag)++;
			break ;
		}
		i++;
	}
	if (!(*flag))
		(*flag) = 2;
}
