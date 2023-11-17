/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/16 23:32:22 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_tokens(char *av, t_tokens **tokens)
{
	int		i;
	int		a;
	int		j;

	i = 0;
	a = 0;
	j = 0;
	init_lists(av, tokens);
	while (av[i] != '\0')
	{
		i++;
		if (!ft_strncmp(&av[i], "<<", 2) || !ft_strncmp(&av[i], ">>", 2) || \
			 av[i] == '|' || av[i] == '<' || av[i] == '>' || !av[i])
		{
			(*tokens)->sign = ft_strdup(ft_substr(av, i, i));
			(*tokens)->token = ft_split(ft_subtokens(av, a, i - a), '\2');
			a = i + 1;
			j++;
			(*tokens) = (*tokens)->next;
		}
	}
	create_pipes(tokens);
	expansion(tokens);
}

int	tokens_num(char *cwd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (cwd[i] == '|' || cwd[i] == '>' || cwd[i] == '<' \
			|| !ft_strncmp(&cwd[i], "<<", 2) || !ft_strncmp(&cwd[i], ">>", 2))
			i++;
		while (!(cwd[i] == '|' || cwd[i] == '>' || cwd[i] == '<' \
			|| !ft_strncmp(&cwd[i], "<<", 2) || !ft_strncmp(&cwd[i], ">>", 2)) && cwd[i])
				i++;
		count++;
		}
	return (count);
}

void	print_dp(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

void free_tokens(void)
{
	int i;

	i = 0;
	if (parser()->tokens)
	{
		while (i < parser()->tokens_n)
		{
			if (parser()->tokens[i].token)
				free_matrix(parser()->tokens[i].token);
			i++;
		}
		free(parser()->tokens);
	}
}

void init_lists(char *av, t_tokens **tokens)
{
	int i;

	i = -1;
	parser()->tokens_n = tokens_num(av);
	(*tokens) = (t_tokens *)malloc(sizeof(t_tokens));// possivel leak!
	(*tokens)->prev = NULL;
	while (++i < parser()->tokens_n)
	{
		(*tokens)->is_file = 0;
		(*tokens)->next = (t_tokens *)malloc(sizeof(t_tokens));
		(*tokens)->next->prev = (*tokens);
		(*tokens) = (*tokens)->next;
	}
	(*tokens)->next = NULL;
	go_head(tokens);
}

void	go_head(t_tokens **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}