/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:39:51 by diomari           #+#    #+#             */
/*   Updated: 2023/12/01 10:30:31 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirections(char **str, int i, t_tokens *tokens)
{
	int	op;

	op = options(str[i]);
	if ((tokens->fd_redir[0] != -1 && tokens->fd_redir[1] != -1) || op == 1)
	{
		if (tokens->fd_redir[0] > 2 && (op == 1 || op == 3))
			close(tokens->fd_redir[0]);
		if (tokens->fd_redir[1] > 2 && (op == 2 || op == 4))
			close(tokens->fd_redir[1]);
		if (op == 2)
			tokens->fd_redir[1] = open(str[i + 1], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (op == 1)
			tokens->fd_redir[0] = ft_heredoc(str[i + 1]);
		else if (op == 3)
			tokens->fd_redir[0] = open(str[i + 1], O_RDONLY, 0644);
		else if (op == 4)
			tokens->fd_redir[1] = open(str[i + 1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		invalid_fds(tokens);
	}
	return (i);
}

int	options(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (1);
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<", 1))
		return (3);
	if (!ft_strncmp(str, ">", 1))
		return (4);
	return (0);
}

void	invalid_fds(t_tokens *token)
{
	if (token->fd_redir[0] == -1)
	{
		perror(" ");
		parser()->exit_status = 1;
		token->error = 1;
	}
	if (token->fd_redir[1] == -1)
	{
		perror(" ");
		parser()->exit_status = 1;
		token->error = 1;
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

void	fds_caseclose(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	go_head(&tmp);
	while (tmp->next)
	{
		if (tmp->fd_redir[0] > 2)
			close(tmp->fd_redir[0]);
		if (tmp->fd_redir[1] > 2)
			close(tmp->fd_redir[1]);
		close(tmp->fd[0]);
		close(tmp->fd[1]);
		tmp = tmp->next;
	}
	token = tmp;
}
