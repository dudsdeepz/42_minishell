/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:59:33 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 10:30:05 by eduarodr         ###   ########.fr       */
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

int	check_dq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = dq_aux(str, i);
			if (!i)
				return (1);
		}
		i++;
	}
	return (0);
}

int	fe_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

char	*search_env(char *token, char **env)
{
	int	i;
	int	size;

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

char	*check_expansion(char *token, int tmp)
{
	int	i;

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
			return (free_da_str(token));
		if (token[i] && !difs("$", token[i]))
		{
			token = get_expansion(token, &i);
			parser()->free_pas_ex = token;
			parser()->pas_exp = 1;
		}
		else
			i++;
	}
	return (token);
}
