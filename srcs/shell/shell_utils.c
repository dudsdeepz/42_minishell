/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/11 14:44:46 by eduarodr         ###   ########.fr       */
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
	tokens()->token = (char **)malloc(sizeof(char *) * get_words(av));
	while (av[i++])
	{
		if (av[i] == '|' || !av[i])
		{
			tokens()->token[j] = ft_substr(av, a, i);
			a = i + 1;
			printf("%s\n", tokens()->token[j]);
			j++;
		}
	}
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