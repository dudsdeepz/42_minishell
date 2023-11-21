/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/21 22:41:59 by eduarodr         ###   ########.fr       */
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
		if (full_check_dq(splited))
			return (0);
		token = init_lists(splited, token);
		executor(&token);
		if (splited[0] && splited)
			free_matrix(splited);
		free_tokens(&token);
	}
	else
		parser()->exit_status = 0;
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
		tokens->fd_master[0] = 0;
		tokens->fd_master[1] = 1;
		tokens->token_size = 1;
		pipe(tokens->fd);
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
			(*tokens)->token[j] = 0;
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
			(*tokens)->token[j++] = ft_strdup(check_expansion(splited[i], 0));
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


int token_size(char **splited, int i)
{
	while (splited[i] && splited[i][0] != '|')
		i++;
	return (1);
}

void	alloc_tokens(t_tokens **tokens)
{
	go_head(tokens);
	while ((*tokens)->next)
	{
		(*tokens)->token = malloc(sizeof(char *) * (*tokens)->token_size);
		(*tokens) = (*tokens)->next;
	}
}


void	free_tokens(t_tokens **tokens)
{
	while ((*tokens)->next)
	{
		if (ft_strlen((*tokens)->path) > 2)
			free((*tokens)->path);
		if ((*tokens)->token)
			free_matrix((*tokens)->token);
		if ((*tokens)->next)
		{
			(*tokens) = (*tokens)->next;
			free((*tokens)->prev);
		}
	}
	free((*tokens));
}