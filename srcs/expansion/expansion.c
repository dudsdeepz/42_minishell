/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/18 17:21:23 by eduarodr         ###   ########.fr       */
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
	if (fk_quotes(token, i))
		return (res);
	while (token[i])
	{
		if (token[i] == '\'')
			i++;
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
	char **new2;
	int j;

	i = 0;
	j = 0;
	new = 0;
	new2 = 0;
	token = quote_killa(token);
	tmp = ft_split(token, '$');
	while (tmp[i])
	{
		new = search_in_env(tmp[i], parser()->envp);
		if (tmp[i + 1])
			new = ft_strjoin(new, tmp[i + 1]);
		i++;
	}
	// printf("%s\n", new);
	// i = -1;
	// while (token[++i])
	// {
	// 	// j = fk_quotes(token[i], j);
	// }
	// if (new2)
	// 	new = join_all(new2);
	return (new);
}

char *search_in_env(char *str, char **env)
{
	int i;
	char **check;
	int j;

	j = 0;
	i = 0;
	while (env[i])
	{
		check = ft_split(env[i], '=');
		if (!ft_strncmp(check[0], str, ft_strlen(check[0])))
			return (check[1]);
		free_matrix(check);
		i++;
	}
	if (ft_isdigit(str[j]))
	{
		j++;
		return (str + 1);
	}
	return (NULL);
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
	while (token[j])
	{
		j++;
		if (token[i] != j && j == '\"')
			return (printf("Unclosed quotes!\n"));
	}
	tmp = token[i++];
	while (token[i] && token[i] != tmp)
		i++;
	if (!token[i])
		return (printf("Unclosed quotes!\n"));
	return (i);
}