/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:26:46 by diomari           #+#    #+#             */
/*   Updated: 2023/12/01 13:00:51 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(t_tokens **tokens)
{
	int		status;
	pid_t	i;

	create_pipes((*tokens));
	go_head(tokens);
	exec_start((*tokens));
	go_head(tokens);
	close_fds(tokens, 1);
	i = 0;
	status = 0;
	while ((*tokens)->next)
	{
		if ((*tokens)->token[0])
		{
			i = waitpid(-1, &status, 0);
			if (i != -1 && WIFEXITED(status))
				parser()->exit_status = WEXITSTATUS(status);
		}
		if (!(*tokens)->next)
			break ;
		(*tokens) = (*tokens)->next;
	}
}

void	exec_doit(t_tokens *tokens)
{
	if (check_built(tokens->token) && lstsize_tokens(tokens) == 1)
	{
		if ((!ft_strncmp(tokens->token[0], "exit", 5)))
			return (_ft_exit(&tokens));
		if (tokens->fd_redir[1] < 2)
			return (tokens->_exec_cmd(&tokens));
	}
	if (fork() == 0)
	{
		if (tokens->next && tokens->fd_redir[1] < 3)
			dup2(tokens->next->fd[1], STDOUT_FILENO);
		else if (tokens->fd_redir[1] > 2)
			dup2(tokens->fd_redir[1], STDOUT_FILENO);
		if (tokens->prev && tokens->fd_redir[0] < 3)
			dup2(tokens->fd[0], STDIN_FILENO);
		else if (tokens->fd_redir[0] > 2)
			dup2(tokens->fd_redir[0], STDIN_FILENO);
		tokens->_exec_cmd(&tokens);
		if (check_built(tokens->token))
			builtins_close(tokens);
		free_all();
		close(0);
		exit(parser()->exit_status);
	}
	close_fds(&tokens, 0);
}

void	exec_start(t_tokens *tokens)
{
	while (tokens->next)
	{
		if (tokens->token[0] && !tokens->error)
		{
			if (ft_path(tokens->token, tokens))
			{
				ft_cmds(tokens);
				exec_doit(tokens);
			}
		}
		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
}

void	close_fds(t_tokens **tokens, int all)
{
	t_tokens	*tmp;

	tmp = (*tokens);
	if (all)
		go_head(tokens);
	while ((*tokens)->next)
	{
		close((*tokens)->fd[0]);
		close((*tokens)->fd[1]);
		if ((*tokens)->fd_redir[0] > 2)
			close((*tokens)->fd_redir[0]);
		if ((*tokens)->fd_redir[1] > 2)
			close((*tokens)->fd_redir[1]);
		if (!all)
			break ;
		(*tokens) = (*tokens)->next;
	}
	(*tokens) = tmp;
}

int	ft_path(char **tokens, t_tokens *token)
{
	char	*tmp;

	if (!check_built(tokens))
	{
		tmp = get_path(tokens[0], parser()->envp);
		if (tmp)
		{
			token->path = ft_strdup(tmp);
			free(tmp);
			return (1);
		}
		else
		{
			token->error = 1;
			token->path = NULL;
			return (0);
		}
	}
	token->path = ft_strdup(tokens[0]);
	return (2);
}
