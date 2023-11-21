/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:26:46 by diomari           #+#    #+#             */
/*   Updated: 2023/11/21 22:10:31 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(t_tokens **tokens)
{
	int status;
	pid_t i;

	kawasaki((*tokens));
	go_head(tokens);
	while ((*tokens)->next)
	{
		if ((*tokens)->token[0])
		{
			i =	waitpid(-1, &status, 0);
			if (i == -1 && WIFEXITED(status))
				parser()->exit_status = WIFEXITED(status);
		}
		if (!(*tokens)->next)
			break ;
		(*tokens) = (*tokens)->next;
	}

}

void kricko(t_tokens *tokens)
{
	if (check_built(tokens->token) && lstsize_tokens(tokens) == 1)
	{
		tokens->_exec_cmd(&tokens);
		return ;
	}
	if (fork() == 0)
	{
		if (tokens->next && tokens->fd_master[1] < 3)
			dup2(tokens->next->fd[1], STDOUT_FILENO);
		else if (tokens->fd_master[1] > 2)
			dup2(tokens->fd_master[1], STDOUT_FILENO);
		if (tokens->prev && tokens->fd_master[0] < 3)
			dup2(tokens->fd[0], STDIN_FILENO);
		else if (tokens->fd_master[0] > 2)
			dup2(tokens->fd_master[0], STDIN_FILENO);
		tokens->_exec_cmd(&tokens);
		close(0);
		exit(parser()->exit_status);
	}
	close_fds(&tokens, 0);
}	

void	kawasaki(t_tokens *tokens)
{
	while (tokens->next)
	{
		if (tokens->token[0])
		{
			ft_path(tokens->token, tokens);
			ft_cmds(tokens);
			kricko(tokens);
		}
		// free_matrix(tokens->token);
		if (!tokens->next)
			break;
		tokens = tokens->next;
	}
}

void close_fds(t_tokens **tokens, int all)
{
	t_tokens *tmp;
	
	tmp = (*tokens);
	if (all)
		go_head(tokens);
	while ((*tokens)->next)
	{
		close((*tokens)->fd[0]);
		close((*tokens)->fd[1]);
		if ((*tokens)->fd_master[0] > 2)
			close((*tokens)->fd_master[0]);
		if((*tokens)->fd_master[1] > 2)
			close((*tokens)->fd_master[1]);
		if (!all)
			break ;
		(*tokens) = (*tokens)->next;
	}
	(*tokens) = tmp;
}


void ft_path(char **tokens, t_tokens *token)
{	
	char *tmp;

	if (!check_built(tokens))
	{
		tmp = get_path(tokens[0], parser()->envp);
		if (ft_strlen(tmp) > 1)
		{
			token->path = ft_strdup(tmp);
			free(tmp);
		}
		else
			token->path = NULL;
		return ;
	}
	return ;
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