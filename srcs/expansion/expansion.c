/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/23 17:08:23 by eduarodr         ###   ########.fr       */
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
			check_expansion(parser()->tokens[i].token[j]);
			j++;
		}
		i++;
	}
}

int	check_expansion(char *token)
{
	// int i;
	// int tmp;

	(void)token;
	return (0);
}
char *get_expansion(char *token)
{
	int i;
	char *new;
	char **tmp;
	char *new2;

	i = 0;
	token = quote_killa(token);
	new = 0;
	tmp = ft_split(token, '$');
	new2 = search_in_env(tmp[0], parser()->envp);
	if (!new2 || !ft_strncmp(new2, "$", 1))
		new2 = tmp[0];
	while (tmp[++i])
	{
		new = search_in_env(tmp[i], parser()->envp);
		if (new)
			new2 = ft_strjoin(new2, new);
	}
	free(token);
	printf("%s\n", new2);
	return (new2);
}

char *search_in_env(char *str, char **env)
{
	int i;
	char **check;
	int j;
	// char *digit_str;

	j = 0;
	i = -1;
	if (!str)
		return ("$");
	while (env[++i])
	{
		check = ft_split(env[i], '=');
		if (!ft_strncmp(check[0], str, ft_strlen(str)))
			return (check[1]);
		free_matrix(check);
	}
	if (ft_isdigit(str[j]))
		return (str + 1);
	str = NULL;
	return (str);
}

int	expansion_wc(char *str)
{
	int i;
	int count;
	
	i = 0;
	count = 1;
	while (str[++i])
	{
		if (str[i] == '\0' || str[i] == '$')
			count++;
	}
	return (count);
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

int expansion_size(char *str)
{
	int i;
	int	size;
	int a;
	char *sizei;

	i = 0;
	a = 0;
	size = 0;
	sizei = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			a = i + 1;
			while (str[i] && ft_isalpha(str[i]))
				i++;
			sizei = search_in_env(ft_substr(str, a, i - a), parser()->envp);
			if (sizei)
				size += ft_strlen(sizei);
		}

		size++;
		i++;	
	}
	return (size);
}
