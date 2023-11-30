/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:58:10 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/30 12:22:29 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	tmp;
	char	*res;

	i = 0;
	j = 0;
	tmp = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) - quote_n(str) + 1));
	while (str && str[i])
	{
		if (str[i] && (!check_sign("'\"", str[i])))
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
	res[j] = 0;
	return (res);
}

int	quote_n(char *str)
{
	int	i;
	int	ct;
	int	qt;

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

int	full_check_dq(char **splited)
{
	int	j;

	j = 0;
	while (splited[j])
	{
		if (check_dq(splited[j]))
			return (printf("Unclose quotes !\n"));
		j++;
	}
	return (0);
}

int	difs(char *sign, char c)
{
	int	i;

	i = 0;
	while (c && sign[i] && c != sign[i])
		i++;
	if (!sign[i])
		return (1);
	return (0);
}

char	*get_status(char *str, int i, char *val)
{
	parser()->free_stts = malloc(ft_strlen(str) - 2 + ft_strlen(val) + 1);
	get_stts_utils(str, i, val, &parser()->free_stts);
	free(val);
	return (parser()->free_stts);
}
