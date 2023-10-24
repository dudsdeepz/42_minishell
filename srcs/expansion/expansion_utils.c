/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:51:34 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/24 15:16:34 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *join_all(char **token)
{
	int i;
	char *new;

	i = 0;
	new = token[0];
	while (token[i])
	{
		i++;
		new = ft_strjoin(new, token[i]);
	}
	return (new);
}

static char *kill_da_quotes(char *str)
{
	int i;
	int j;
	char tmp;
	char *res;
	
	i = 0;
	j = 0;
	tmp = 0;
	res = malloc(sizeof(char *) * ft_strlen(str) - quote_n(str) + 1);
	while (str && str[i])
	{
		if (str[i] && !check_sign("'\"", str[i]))
		{
			tmp = str[i];
			i++;
			while (str[i] && str[i] != tmp)
				res[j++] = str[i++];
		}
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	check_sign(char *str, char c)
{
	int i;

	i = 0;
	while (c && str[i] && c != str[i])
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	quote_n(char *str)
{
	int i;
	int ct;
	int qt;

	i = 0;
	ct = 0;
	while (str[i])
	{
		if (str[i] && !check_sign("'\"", str[i]))
		{
			qt = str[i];
			i++;
			while (str[i] && str[i] != qt)
				i++;
			ct += 2;
		}
		i++;
	}
	return (ct);
}

char *quote_killa(char *str)
{
	char *res;

	res = kill_da_quotes(str);
	free(str);
	return (res);
}

int fk_quotes(char *token, int i)
{
	char tmp;

	tmp = token[i++];
	while (token[i] && token[i] != tmp)
		i++;
	if (!token[i])
	{
		printf("Unclosed quotes!\n");
		(*synt())++;
	}
	return (i);
}

int *synt(void)
{
	static int bruh;
	return (&bruh);
}