/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/11 14:25:21 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_tokens(char *av)
{
	int	i;
	int j;
	int a;
	
	i = 0;
	j = 0;
	a = 0;
	tokens()->token = malloc(sizeof(char*) * get_words(av));
	a = 0;
	while (av[i++])
	{
		if (av[i] == '|' || !av[i])
		{
			printf("token: %d\n", a);
			a++;
		}
	}
	j = 0;
	return(tokens()->token);
}

int	get_words(char *cwd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (cwd[i] == '|' || cwd[i] == '>')
			i++;
		while (!(cwd[i] == '|' || cwd[i] == '>') && cwd[i])
				i++;
		count++;
		}
	return (count);
}