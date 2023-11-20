/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:39:51 by diomari           #+#    #+#             */
/*   Updated: 2023/11/20 16:53:08 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int redirections(t_tokens *tokens)
{
	int op;
	
	op = options(tokens);
	if ((tokens->fd_master[0] != -1 && tokens->fd_master[1] != -1) || op == 1)
	{
		if (tokens->fd_master[0] > 2 && (op == 1 || op == 3))
			close(tokens->fd_master[0]);
		if (tokens->fd_master[1] > 2 && (op == 2 || op == 4))
			close(tokens->fd_master[1]);
		if (op == 2)
			tokens->fd_master[1] = open(tokens->next->token[0], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (op == 1)
			tokens->fd_master[0] = ft_heredoc(tokens->next->token[0]);
		else if (op == 3)
			tokens->fd_master[0] = open(tokens->next->token[0], O_RDONLY, 0644);
		else if (op == 4)
			tokens->fd_master[1] = open(tokens->next->token[0], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (op)
			tokens->next->is_file = 1;
		// invalid_fds(tokens);
	}
	return (1);
}


int	options(t_tokens *token)
{
	if (!ft_strncmp(token->sign, "<<", 2))
		return (1);
	if (!ft_strncmp(token->sign, ">>", 2))
		return (2);
	if (!ft_strncmp(token->sign, "<", 1))
		return (3);
	if (!ft_strncmp(token->sign, ">", 1))
		return (4);
	return (0);
}

void	invalid_fds(t_tokens *token)
{
	if (token->fd_master[0] == -1)
	{
		perror("");
		token->master_error[0] = 1;
	}
	if (token->fd_master[1] == -1)
	{
		perror("");
		token->master_error[1] = 1;
	}
}

int	check_double_red(char *av, int i)
{
	if (av[i] == '<' && av[i + 1] == '<')
		return (1);
	else if (av[i] == '>' && av[i + 1] == '>')
		return (2);
	return (0);
}