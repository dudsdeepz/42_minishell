/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/03 16:22:37 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_tokens(char *cwd)
{
	int	j;
	int	i;
	int	a;

	j = 0;
	i = 0;
	a = 0;
	if (tokens()->token)
		free(tokens()->token);
	tokens()->token = malloc(sizeof(char *) * get_words(cwd));
	while (cwd[i])
	{
		while ((cwd[i] == ' ' || cwd[i] == '|' || cwd[i] == '>') && cwd[i])
			i++;
		if (ft_isprint(cwd[i]))
		{
			a = i;
			while ((cwd[i] != '|' || cwd[i] != '>') && cwd[i])
				i++;
			tokens()->token[j] = ft_substr(cwd, a, i);
			j++;
		}
	}
	j = 0;
	while (tokens()->token[j])
	{
		printf("%s\n", tokens()->token[j]);
		j++;
	}
}

int	get_words(char *cwd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (cwd[i] == ' ' || cwd[i] == '|' || cwd[i] == '>')
			i++;
		if (!(cwd[i] == ' ' || cwd[i] == '|' || cwd[i] == '>') && cwd[i])
		{
			while (!(cwd[i] == '|' || cwd[i] == '>') && cwd[i])
				i++;
			count++;
		}
	}
	return (count);
}
