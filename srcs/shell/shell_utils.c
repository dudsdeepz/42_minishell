/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/20 18:34:28 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	freedy_fazbear(char *av, t_tokens *tokens)
{
	char 	**splited;

	/*
		do heredoc;
		fix quote;
		fix leaks;
		fix executor(pipes & redirections)
	*/
	splited = NULL;
	if (av)
		splited = ft_split(av, '\2');
	if (full_check_dq(splited))
		return (1);
	tokens = (t_tokens *)malloc(sizeof(t_tokens *));
	init_lists(splited, &tokens);
	get_tokens_size(splited, &tokens);
	alocate_tokens(&tokens);
	separeites_tokens(&tokens, splited);
	create_pipes(&tokens);
	executor(tokens);
	free_matrix(splited);
	go_head(&tokens);
	free_tokens(tokens);
	free(av);
	return (0);
}

int	tokens_num(char **cwd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (is_sign(cwd[i]) || !cwd[i + 1])
			count++;
		i++;
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

void free_tokens(t_tokens *token)
{
	while (token->next)
	{
		if (token->path)
			free(token->path);
		token = token->next;
		free(token->prev);
	}
	free(token);
}

void init_lists(char **av, t_tokens **tokens)
{
	int count;

	count = tokens_num(av);
	(*tokens) = (t_tokens *)malloc(sizeof(t_tokens));// possivel leak!
	(*tokens)->prev = NULL;
	while (count--)
	{
		(*tokens)->token_size = 1;
		(*tokens)->is_file = 0;
		(*tokens)->sign = NULL;
		(*tokens)->next = (t_tokens *)malloc(sizeof(t_tokens));
		(*tokens)->next->prev = (*tokens);
		(*tokens) = (*tokens)->next;
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

	i = 0;
	go_head(tokens);
	while (splited[i])
	{
		if (is_sign(splited[i]) || !splited[i + 1])
			(*tokens) = (*tokens)->next;
		(*tokens)->token_size++;
		i++;
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
	else if(!ft_strncmp(sign, ">>", 2))
		return (1);
	else if(!ft_strncmp(sign, "<<", 2))
		return (1);
	else if(!ft_strncmp(sign, ">", 1))
		return (1);
	else if(!ft_strncmp(sign, "<", 1))
		return (1);
	return (0);
}

void	separeites_tokens(t_tokens **tokens, char **splited)
{
	int i;
	int j;
	int exp_tmp;

	i = -1;
	j = 0;
	exp_tmp = 0;
	go_head(tokens);
	while (splited[++i])
	{
		if (!is_sign(splited[i]) && splited[i])
		{
			(*tokens)->token[j++] = check_expansion(splited[i], exp_tmp);
			if (!splited[i + 1])
				(*tokens)->token[j++] = 0;
		}
		else
		{
			(*tokens)->token[j] = 0;
			if (splited[i])
				(*tokens)->sign = ft_strdup(splited[i]);
			if (!ft_strncmp(splited[i], "<<", 2))
			{
				(*tokens)->is_file = 1;
				(*tokens)->token[j++] = ft_strdup(splited[i + 1]);
			}
			j = 0;
			(*tokens) = (*tokens)->next;
		}
	}
}
