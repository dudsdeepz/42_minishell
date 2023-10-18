/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/17 16:57:24 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void expansion(void)
{
	int i;
	
	i = 0;
	while (i < parser()->tokens_n)
	{
		if (check_expansion(parser()->tokens[i].token))
			parser()->tokens[i].token = get_expansion(parser()->tokens[i].token);
		i++;
	}
}

int	check_expansion(char **token)
{
	int i;

	i = 0;
	while (token[i])
	{
		if (!ft_strncmp(token[i], "$", 1))
			return (1);
		i++;
	}
	return (0);
}

char **get_expansion(char **token)
{
	int i;
	char **splited;
	int j;

	i = -1;
	while (token[++i])
	{
		j = 0;
		if (!ft_strncmp(token[i], "$", 1))
		{
			splited = ft_split(token[i], '$');
			while (splited[j])
			{
				free(token[i]);
				if (search_in_env(splited[j], parser()->envp))
					token[i] = ft_strdup(search_in_env(splited[j], parser()->envp));
				else
					token[i] = 0;
				j++;
			}
			free_matrix(splited);
		}
	}
	return (token);
}

char *search_in_env(char *str, char **env)
{
	int i;
	char **check;

	i = 0;
	while (env[i])
	{
		check = ft_split(env[i], '=');
		if (!ft_strncmp(check[0], str, ft_strlen(check[0])))
			return (check[1]);
		free_matrix(check);
		i++;
	}
	return (NULL);
}