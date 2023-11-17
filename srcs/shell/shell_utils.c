/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/17 22:35:17 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_tokens(char *av, t_tokens **tokens)
{
	char 	**splited;

	init_lists(av, tokens);
	splited = ft_split(av, '\2');
	get_tokens_size(splited, tokens);
	alocate_tokens(tokens);
	separeites_tokens(tokens, splited);
	create_pipes(tokens);
	expansion(tokens);
	go_head(tokens);
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
	
	i = 0;
	while (str[i] != 0)
	{
		printf("%s\n", str[i]);
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

	i = 0;
	parser()->tokens_n = tokens_num(av);
	(*tokens) = (t_tokens *)malloc(sizeof(t_tokens));// possivel leak!
	(*tokens)->prev = NULL;
	while (i < parser()->tokens_n)
	{
		(*tokens)->token_size = 0;
		(*tokens)->is_file = 0;
		(*tokens)->sign = NULL;
		(*tokens)->next = (t_tokens *)malloc(sizeof(t_tokens));
		(*tokens)->next->prev = (*tokens);
		(*tokens) = (*tokens)->next;
		i++;
	}
	(*tokens)->next = NULL;
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

void	get_tokens_size(char **splited, t_tokens **tokens)
{
	int i;

	i = -1;
	go_head(tokens);
	while (splited[++i])
	{
		if (!ft_strncmp(splited[i], "|", 1) || !ft_strncmp(splited[i], ">>", 1) || !ft_strncmp(splited[i],	 ">", 1) || !ft_strncmp(splited[i], "<", 1)\
			|| !ft_strncmp(splited[i], "<", 1))
		{
			(*tokens) = (*tokens)->next;
			(*tokens)->token_size--;
		}
		(*tokens)->token_size++;
	}
}

void	alocate_tokens(t_tokens **tokens)
{
	go_head(tokens);
	while ((*tokens)->next)
	{
		(*tokens)->token = malloc(sizeof(char *) * (*tokens)->token_size + 10);
		(*tokens) = (*tokens)->next;
	}
}

int	is_sign(char *sign)
{
	if (!ft_strncmp(sign, "|", 1))
		return (1); 
	else if(!ft_strncmp(sign, ">", 1))
		return (1);
	else if(!ft_strncmp(sign, ">>", 1))
		return (1);
	else if(!ft_strncmp(sign, "<<", 1))
		return (1);
	else if(!ft_strncmp(sign, ">>", 1))
		return (1);
	return (0);
}

void	separeites_tokens(t_tokens **tokens, char **splited)
{
	int i;
	int j;

	i = 0;
	j = 0;
	go_head(tokens);
	while (splited[i])
	{
		if (is_sign(splited[i]))
		{
			(*tokens)->sign = ft_strdup(splited[i]);
			(*tokens)->token[j++] = 0;
			j = 0;
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			i++;
		}
		(*tokens)->token[j++] = ft_strdup(splited[i]);
		i++;
	}
	(*tokens)->token[j] = 0;
}