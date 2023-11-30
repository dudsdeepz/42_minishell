/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:08:34 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/29 17:45:49 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_ft_echo(t_tokens **token)
{
	int	j;

	j = 1;
	if (list_size((*token)->token) > 1)
	{
		while ((*token)->token[j])
		{
			if (!n_case((*token)->token[j]))
				break ;
			j++;
		}
	}
	while ((*token)->token[j])
	{
		printf ("%s", (*token)->token[j]);
		if ((*token)->token[j + 1])
			printf(" ");
		j++;
	}
	if (!(list_size((*token)->token) > 1 && n_case((*token)->token[1])) \
		|| !(*token)->token[1][0])
		printf("\n");
	parser()->exit_status = 0;
}

int	n_case(char *flag)
{
	int	i;

	i = -1;
	while (flag[++i])
	{
		if ((!i && flag[i] != '-') || (i && flag[i] != 'n'))
			return (0);
	}
	return (1);
}
