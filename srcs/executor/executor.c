/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:26:46 by diomari           #+#    #+#             */
/*   Updated: 2023/11/17 01:06:07 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(t_tokens *tokens)
{
	kawasaki(tokens);
	go_head(&tokens);
	while (tokens->next)
	{
		if (tokens->token[0])
			waitpid(-1, &parser()->exit_status, 1);
		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
}

void kricko(t_tokens *tokens)
{
	if (lstsize_tokens(tokens) == 1)
	{
		one_command(tokens);
		return ;
	}
	if (fork() == 0)
	{
		if (tokens->prev && tokens->fd_master[0] < 3)
			ft_dup2(tokens->fd[0], STDOUT_FILENO);
		else if (tokens->fd_master[0] > 2)
			ft_dup2(tokens->fd_master[0], STDOUT_FILENO);
		if (tokens->next && tokens->fd_master[1] < 3)
			ft_dup2(STDIN_FILENO, tokens->next->fd[1]);
		else if (tokens->fd_master[1] > 2)
			ft_dup2(STDIN_FILENO, tokens->fd_master[1]);
		estriper(tokens);
		close(0);
		exit(0);
	}
	else if (tokens->proc > 0)
		wait(0);
	close_fds(tokens, 0);
}

void	estriper(t_tokens *tokens)
{
	if (!exec_cmds(tokens->token))
	{
		close_fds(tokens, 0);
		execve(tokens->path, tokens->token, parser()->envp);
		close(0);
		close(1);
		exit(0);
	}
}

void	kawasaki(t_tokens *tokens)
{
	while (tokens && tokens->next)
	{
		if (tokens->token[0] && !tokens->is_file)
		{
			tokens->path = ft_path(tokens->token);
			kricko(tokens);
		}
		if (!tokens->next)
			break;
		tokens = tokens->next;
	}
}

void close_fds(t_tokens *tokens, int all)
{
	t_tokens *tmp;
	
	tmp = tokens;
	if (all)
		go_head(&tokens);
	while (tokens->next)
	{
		close(tokens->fd[0]);
		close(tokens->fd[1]);
		if (tokens->fd_master[0] > 2)
			close(tokens->fd_master[0]);
		if(tokens->fd_master[1] > 2)
			close(tokens->fd_master[1]);
		if (!all)
			break ;
		tokens = tokens->next;
	}
	tokens = tmp;
}

void	create_pipes(t_tokens **tokens)
{
	if (parser()->tokens_n == 1)
		return ;
	go_head(tokens);
	while((*tokens)->next)
	{
		(*tokens)->fd_master[0] = 0;
		(*tokens)->fd_master[1] = 1;
		pipe((*tokens)->fd);
		if (options((*tokens)->sign))
			redirections((*tokens));
		(*tokens) = (*tokens)->next;
	}
}

void	one_command(t_tokens *token)
{
	if (!exec_cmds(token->token) && ft_strlen(token->path) > 0)
	{
		token->proc = fork();
		if (token->proc == 0)
			execve(token->path, token->token, parser()->envp);
		else if (token->proc > 0)
			wait(0);
		waitpid(token->proc, &parser()->exit_status, 0);
	}
}


char	*ft_path(char **token)
{
	char *path;
	
	path = NULL;
	if (!check_built(token))
	{
		path = get_path(*token, parser()->envp);
		if (path)
			return (ft_strdup(path));
		return (0);
	}
	return (0);
}


void ft_dup2(int input, int output)
{
	if (input != STDIN_FILENO)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (output != STDOUT_FILENO	)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}