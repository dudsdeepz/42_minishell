/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:22 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 12:21:30 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	alloc_tokens(t_tokens **tokens)
{
	go_head(tokens);
	while ((*tokens)->next)
	{
		(*tokens)->token = malloc(sizeof(char *) * (*tokens)->token_size);
		(*tokens) = (*tokens)->next;
	}
}

void	get_tokens_size(char **splited, t_tokens **tokens)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	go_head(tokens);
	while (splited[++i] && splited)
	{
		if (splited[i][0] == '|')
			(*tokens) = (*tokens)->next;
		else if (options(splited[i]))
			++i;
		else
			(*tokens)->token_size++;
	}
	alloc_tokens(tokens);
}

t_tokens	*separeites_tokens(t_tokens **tokens, char **splited)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	go_head(tokens);
	while (splited && splited[++i])
	{
		if (splited[i][0] == '|')
		{
			(*tokens)->token[j++] = 0;
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			j = 0;
		}
		else if (options(splited[i]))
		{
			splited[i + 1] = file_quotes(splited[i + 1]);
			redirections(splited, i++, (*tokens));
		}
		else
			(*tokens)->token[j++] = remove_quotes(splited[i]);
	}
	(*tokens)->token[j] = 0;
	return ((*tokens));
}

static void	aux_prepstr(void)
{
	if (parser()->pas_exp)
	{
		free(parser()->exp_var);
		parser()->exp_var = NULL;
	}
}

char	**prep_str(char **str)
{
	int		i;
	char	*tmp;	

	i = -1;
	parser()->hd = 0;
	while (str[++i])
	{
		if (is_sign(str[i]))
			i++;
		tmp = ft_strdup(check_expansion(str[i], 0));
		free(str[i]);
		str[i] = ft_strdup(tmp);
		parser()->was_redir = str[i];
		free(tmp);
		aux_prepstr();
		if (parser()->free_stts)
		{
			free(parser()->free_stts);
			parser()->free_stts = NULL;
		}
		tmp = NULL;
	}
	parser()->splited = str;
	return (str);
}
