/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/17 15:01:39 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_tokens(char *av, t_tokens **tokens)
{
	int		i;
	int		j;
	char 	**splited;

	i = 0;
	j = 0;
	init_lists(av, tokens);
	splited = ft_split(av, '\2');
	while (splited[i] != 0)
	{
		if (!ft_strncmp(splited[i], ">>", 1) || !ft_strncmp(splited[i], ">", 1) || !ft_strncmp(splited[i], "<<", 1) || !ft_strncmp(splited[i], ">", 1) || !ft_strncmp(splited[i], "|", 1) || !splited[i])
		{
			stokens_num(splited, j, i);
			j = i + 1;
		}
		i++;
	}
}
	// create_pipes(tokens);
	// expansion(tokens);

int	tokens_num(char *cwd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (cwd[i] == '|' || cwd[i] == '>' || cwd[i] == '<' \
			|| check_double_red(cwd, i))
			i++;
		while (!(cwd[i] == '|' || cwd[i] == '>' || cwd[i] == '<' \
			|| check_double_red(cwd, i)) && cwd[i])
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

int get_sign(t_tokens *tokens, int i, char *av)
{
	if (check_double_red(av, i))
	{
		tokens->sign = ft_strdup(ft_substr(av, i, i + 1));
		return (i);
	}
	else
		tokens->sign = ft_strdup(ft_substr(av, i, i));
	return (0);
}

int	stokens_num(char **cwd, int start, int end)
{
	int a;

	a = 0;
	while (ft_strncmp(cwd[start], cwd[end], ft_strlen(cwd[end])))
	{
		a++;
		start++;
	}
	printf("a: %d\n", a);
	return (a);
}