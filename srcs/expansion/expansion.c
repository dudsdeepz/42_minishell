/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 21:56:00 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	dolutil(int *tmp)
{
	if (!(*tmp))
		*tmp = 1;
	else
		*tmp = 0;
}

bool token_valid_char(char a)
{
	return ((ft_isalnum(a)) || (a == '_'));
}

static void v_helper(char *token, char *str, int start, int end, char *res)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] && i >= start - 1 && i <= end)
		{
			i = -1;
			if (str)
			{
				while(str[++i])
					res[j++] = str[i];
			}
			i = end + 1;
		}
		if (token[i] && (i < start || i > end))
			res[j] = token[i];
		if (token[i])
			i++;
		j++;
	}
}

char *check_expansion(char *token, int tmp)
{
	int i;

	i = 0;
	while (token[i])
	{
		if (!token[i])
			return (token);
		if (token[i] == '\"' && token[i])
			dolutil(&tmp);
		if (token[i] && !difs("\'", token[i]) && !tmp)
			i = fk_quotes(token, i);
		if (*synt())
			return(free_da_str(token));
		if (token[i] && !difs("$", token[i]))
			token = get_expansion(token, &i);
		else
			i++;
	}
	if (!ft_strncmp(token, "\"", 1) || !ft_strncmp(token, "\'", 1))
		token = quote_killa(token);
	return (token);
}

char *get_expansion(char *token, int *i)
{
	int 	a;
	char *res;

	a = (*i) + 1;
	if (token[a] == '?')
	{
		return (ft_itoa(parser()->exit_status));
		(*i)++;
	}
	while (token[a] && token_valid_char(token[a]))
		a++;
	if (a == (*i) + 1)
	{
		(*i)++;
		return (token);
	}
	res = fk_token(token, search_env(ft_substr(token, (*i) + 1, a - 1), \
		parser()->envp), (*i) + 1, a - 1);
	return (res);
}

char *search_env(char *token, char **env)
{
	int i;
	int size;

	i = -1;
	if (ft_isdigit(*token))
		return (ft_strdup(token + 1));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], token, fe_sign(env[i])) && \
		!token[fe_sign(env[i])])
			break ;
	}
	size = ft_strlen(token);
	if (token)
		free (token);
	if (!env[i])
		return (NULL);
	return (ft_strdup(env[i] + size + 1));
}

char *fk_token(char *token, char *str, int i, int a)
{
	char *res;

	if (str)
		res = malloc(ft_strlen(token) - (a - i + 2) + ft_strlen(str) + 1);
	else
		res = malloc(ft_strlen(token) - (a - i + 2) + 1);
	v_helper(token, str, i, a, res);
	if (str)
		res[ft_strlen(token) - (a - i + 2) + ft_strlen(str)] = 0;
	else
		res[ft_strlen(token) - (a - i + 2)] = 0;
	if (str)
		free(str);
	return (res);
}

int fe_sign(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int difs(char *sign, char c)
{
	int i;

	i = 0;
	while (c && sign[i] && c != sign[i])
		i++;
	if (!sign[i])
		return (1);
	return (0);
}

char	*free_da_str(char *str)
{
	free(str);
	str = NULL;
	return (str);
}

int	check_dq(char *str)
{
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = str[i++];
			while (str[i] != tmp)
			{
				if (str[i] == tmp)
					return (0);
				else if (str[i] == 0)
					return (1);
			}
			// if (!str[i] && str[i - 1] != tmp)
			// 	return (1);
			// if (str[i] == '\0')
			// 	return (1);				
		}
		i++;
	}
	return (0);
}

int	full_check_dq(char **splited)
{
	int j;

	j = 0;
	while (splited[j])
	{
		if (check_dq(splited[j]))
			return (printf("Unclose quotes !\n"));
		j++;
	}
	return (0);
}