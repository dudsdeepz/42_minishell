/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/24 14:35:36 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	token_valid_char(char a)
{
	return ((ft_isalnum(a)) || (a == '_'));
}

static void	v_helper(char *token, char *str, int start, int end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] && i >= start - 1 && i <= end)
		{
			i = -1;
			if (str)
			{
				while (str[++i])
					parser()->exp_var[j++] = str[i];
			}
			i = end + 1;
		}
		if (token[i] && (i < start || i > end))
			parser()->exp_var[j] = token[i];
		if (token[i])
			i++;
		j++;
	}
}

char	*get_expansion(char *token, int *i)
{
	int		a;
	char	*tmp;
	char	*res;

	a = (*i) + 1;
	if (token[a] == '?')
	{
		tmp = ft_itoa(parser()->exit_status);
		return (tmp);
		(*i)++;
	}
	while (token[a] && token_valid_char(token[a]))
		a++;
	if (a == (*i) + 1)
	{
		(*i)++;
		return (token);
	}
	res = exp_token(token, search_env(ft_substr(token, (*i) + 1, a - 1), \
		parser()->envp), (*i) + 1, a - 1);
	return (res);
}

char	*exp_token(char *token, char *str, int i, int a)
{
	if (str)
		parser()->exp_var = malloc(ft_strlen(token) \
			- (a - i + 2) + ft_strlen(str) + 1);
	else
		parser()->exp_var = malloc(ft_strlen(token) - (a - i + 2) + 1);
	v_helper(token, str, i, a);
	if (str)
		parser()->exp_var[ft_strlen(token) - (a - i + 2) + ft_strlen(str)] = 0;
	else
		parser()->exp_var[ft_strlen(token) - (a - i + 2)] = 0;
	if (str)
		free(str);
	return (parser()->exp_var);
}

char	*free_da_str(char *str)
{
	free(str);
	str = NULL;
	return (str);
}
