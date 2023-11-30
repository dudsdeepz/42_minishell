/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:51:34 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/29 20:20:41 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_all(char **token)
{
	int		i;
	char	*new;

	i = 0;
	new = token[0];
	while (token[i])
	{
		i++;
		new = ft_strjoin(new, token[i]);
	}
	return (new);
}

int	check_sign(char *str, char c)
{
	int	i;

	i = 0;
	while (c && str[i] && c != str[i])
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	fk_quotes(char *token, int i)
{
	char	tmp;

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

int	*synt(void)
{
	static int	bruh;

	return (&bruh);
}

int	dq_aux(char *str, int i)
{
	int	tmp;

	tmp = str[i];
	while (str[++i] != tmp && str[i])
		continue ;
	if (!str[i])
		return (0);
	else
		return (i);
}
