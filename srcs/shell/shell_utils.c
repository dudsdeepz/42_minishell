/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 21:55:06 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	shell_output(char *av)
{
	char 	**splited;
	t_tokens *token;

	splited = NULL;
	token = NULL;
	if (ft_strlen(av) > 0)
	{
		splited = ft_split(av, '\2');
		if (ft_strlen(splited[0]) > 0)
		{
			if (full_check_dq(splited))
				return (0);
			token = init_lists(splited, token);
			executor(&token);
			free_tokens(token);
		}
		free_matrix(splited);
	}
	return (0);
}

int	tokens_num(char **cwd)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (cwd[++i])
	{
		if (cwd[i][0] == '|' || !cwd[i + 1])
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

t_tokens *init_lists(char **av, t_tokens *tokens)
{
	int count;

	count = tokens_num(av);
	tokens = malloc(sizeof(t_tokens));
	tokens->prev = NULL;
	while (count--)
	{
		tokens->fd_redir[0] = 0;
		tokens->fd_redir[1] = 1;
		tokens->token_size = 1;
		tokens->token = NULL;
		tokens->path = NULL;
		tokens->next =	malloc(sizeof(t_tokens));
		tokens->next->prev = tokens;
		tokens = tokens->next;
	}
	tokens->next = NULL;
	get_tokens_size(av, &tokens);
	separeites_tokens(&tokens, av);
	return (tokens);
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

t_tokens *separeites_tokens(t_tokens **tokens, char **splited)
{
	int i;
	int j;

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
			redirections(splited, i, (*tokens));
			i++;
		}
		else
		{
			(*tokens)->token[j++] = ft_strdup(check_expansion(splited[i], 0));
			free(parser()->tmp_var);
		}
	}
	(*tokens)->token[j++] = 0;
	return ((*tokens));
}

void	get_tokens_size(char **splited, t_tokens **tokens)
{
	int i;

	i = -1;
	go_head(tokens);
	while (splited[++i] && splited)
	{
		if (splited[i][0] == '|')
			(*tokens) = (*tokens)->next;
		else if (options(splited[i]))
			i++;
		else			
			(*tokens)->token_size++;
	}
	alloc_tokens(tokens);
}

void	alloc_tokens(t_tokens **tokens)
{
	go_head(tokens);
	while ((*tokens)->next)
	{
		(*tokens)->token = malloc(sizeof(char *) * (*tokens)->token_size);
		pipe((*tokens)->fd);
		(*tokens) = (*tokens)->next;
	}
}


void	free_tokens(t_tokens *token)
{
	while (token->prev)
	{
		token = token->prev;
		if (token->token[0] != NULL && token->token)
			free_matrix(token->token);
		free(token->next);
	}
	free(token);
}