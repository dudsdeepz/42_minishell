/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 13:06:08 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	shell_output(char *av, char **splited)
{
	t_tokens	*token;

	token = NULL;
	if (ft_strlen(av) > 0)
	{
		splited = ft_split(av, '\2');
		if (ft_strlen(splited[0]) > 0)
		{
			if (full_check_dq(splited))
			{
				free_matrix(splited);
				return (0);
			}
			token = init_lists(prep_str(splited), token);
			if (!parser()->pause)
			{
				executor(&token);
				free_matrix(splited);
				aux_shelloutput(token);
			}
		}
		else
			free_matrix(splited);
	}
	return (0);
}

int	tokens_num(char **cwd)
{
	int	i;
	int	count;

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
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

t_tokens	*init_lists(char **av, t_tokens *tokens)
{
	int	count;

	count = tokens_num(av);
	parser()->list_size = count;
	tokens = malloc(sizeof(t_tokens));
	tokens->prev = NULL;
	while (count--)
	{
		tokens->fd_redir[0] = 0;
		tokens->fd_redir[1] = 1;
		tokens->fd[0] = 0;
		tokens->token_size = 1;
		tokens->token = NULL;
		tokens->path = NULL;
		tokens->error = 0;
		tokens->next = malloc(sizeof(t_tokens));
		tokens->next->prev = tokens;
		tokens->next->fd[1] = 1;
		tokens = tokens->next;
	}
	parser()->head_token = tokens;
	tokens->next = NULL;
	get_tokens_size(av, &tokens);
	separeites_tokens(&tokens, av);
	return (tokens);
}

int	is_sign(char *sign)
{
	if (!ft_strncmp(sign, "|", 2))
		return (1);
	else if (!ft_strcmp(sign, ">>"))
		return (1);
	else if (!ft_strcmp(sign, "<<"))
		return (1);
	else if (!ft_strncmp(sign, ">", 2))
		return (1);
	else if (!ft_strncmp(sign, "<", 2))
		return (1);
	return (0);
}
