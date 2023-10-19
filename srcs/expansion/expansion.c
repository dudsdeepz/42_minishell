/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/19 13:45:49 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void expansion(void)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (i < parser()->tokens_n)
	{
		while (parser()->tokens[i].token[j])
		{
			if (check_expansion(parser()->tokens[i].token[j]))
				parser()->tokens[i].token[j] = get_expansion(parser()->tokens[i].token[j]);
			j++;
		}
		i++;
	}
}

int	check_expansion(char *token)
{
	int i;
	int	res;

	i = 0;
	res = 0;
	// while (token[i++])
	// 	if (fk_quotes(token, i))
	// 		return (res);
	// i++;
	while (token[i])
	{
		if (token[i] == '$')
		{
			res = 1;
			break;
		}
		i++;
	}
	return (res);
}

char *get_expansion(char *token)
{
	int i;
	char **tmp;
	char *new;
	char *new2;

	i = 0;
	token = quote_killa(token);
	tmp = ft_split(token, '$');
	new = 0;
	new2 = search_in_env(tmp[0], parser()->envp);
	while (tmp[++i])	
	{
		new = search_in_env(tmp[i], parser()->envp);
		if (new)
			new2 = ft_strjoin(new2, new);
	}
	return (new2);
}

char *search_in_env(char *str, char **env)
{
	int i;
	char **check;
	int j;

	j = 0;
	i = -1;
	while (env[++i])
	{
		check = ft_split(env[i], '=');
		if (!ft_strncmp(check[0], str, ft_strlen(str)))
			return (check[1]);
		free_matrix(check);
	}
	if (ft_isdigit(str[j]))
	{
		j++;
		return (str + 1);
	}
	str = NULL;
	return (str);
}

char	*expansion_wg(char *splited)
{
	if (search_in_env(splited, parser()->envp))
		splited = ft_strdup(search_in_env(splited, parser()->envp));
	else
		splited = 0;
	return (splited);
}

int fk_quotes(char *token, int i)
{
	char tmp;
	int j;

	j = 0;
	i = 0;

	tmp = token[i++];
	while (token[i] && token[i] != tmp)
		i++;
	if (!token[i])
		return (printf("Unclosed quotes!\n"));
	return (i);
}