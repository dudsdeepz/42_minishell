/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:56:46 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/29 21:00:04 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	total_tokens_size(t_tokens **tokens)
{
	int	count;

	count = 0;
	go_head(tokens);
	while ((*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		count++;
	}
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
			i++;
		return (s1[i] - s2[i]);
	}
	return (1);
}

void	go_head(t_tokens **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}

void	free_matrix(char **mtx)
{
	int	p;

	p = -1;
	if (mtx != NULL)
	{
		while (mtx[++p])
		{
			if (mtx[p] != NULL)
			{
				free(mtx[p]);
				mtx[p] = NULL;
			}
		}
	}
	if (mtx[p])
	{
		free(mtx[p]);
		mtx[p] = NULL;
	}
	free(mtx);
	mtx = NULL;
}

int	free_path_helper(char *str, char *command, char **path)
{
	free_matrix(path);
	if (!str)
	{
		free_str_h(str, command);
		if (str)
			free(str);
		return (0);
	}
	if (str)
		free(str);
	return (1);
}
