/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:48:45 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 13:47:00 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_ft_pwd(t_tokens **token)
{
	char	*cwd;

	(void)token;
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	close_fds(token, 0);
}

void	_ft_env(t_tokens **token)
{
	char	**env;
	int		i;

	i = 0;
	(void)token;
	env = parser()->envp;
	while (env[i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		++i;
	}
	close_fds(token, 0);
	return ;
}

void	ft_cmds(t_tokens *token)
{
	if (!ft_strcmp(token->token[0], "pwd"))
		token->_exec_cmd = _ft_pwd;
	else if (!ft_strcmp(token->token[0], "cd"))
		token->_exec_cmd = _ft_cd;
	else if (!ft_strcmp(token->token[0], "echo"))
		token->_exec_cmd = _ft_echo;
	else if (!ft_strcmp(token->token[0], "env"))
		token->_exec_cmd = _ft_env;
	else if (!ft_strcmp(token->token[0], "exit"))
		token->_exec_cmd = _ft_exit;
	else if (!ft_strcmp(token->token[0], "export"))
		token->_exec_cmd = _ft_export;
	else if (!ft_strcmp(token->token[0], "unset"))
		token->_exec_cmd = _ft_unset;
	else
		token->_exec_cmd = _ft_exec_cmd;
}

int	check_built(char **linei)
{
	if (linei)
	{
		if (linei[0] && !ft_strcmp(linei[0], "pwd"))
			return (1);
		else if (linei[0] && !ft_strcmp(linei[0], "env"))
			return (1);
		else if (linei[0] && !ft_strcmp(linei[0], "echo"))
			return (1);
		else if (linei[0] && !ft_strcmp(linei[0], "exit"))
			return (1);
		else if (linei[0] && !ft_strcmp(linei[0], "cd"))
			return (1);
		else if (linei[0] && !ft_strcmp(linei[0], "export"))
			return (1);
		else if (linei[0] && !ft_strcmp(linei[0], "unset"))
			return (1);
	}
	return (0);
}

void	_ft_exec_cmd(t_tokens **token)
{
	fds_caseclose((*token));
	close_fds(token, 1);
	if (execve((*token)->path, (*token)->token, parser()->envp) == -1)
	{
		if (!ft_strchr((*token)->token[0], '/') \
			&& !access((*token)->token[0], X_OK))
		{
			ft_putstr_fd(" command not found\n", STDERR_FILENO);
			parser()->exit_status = 127;
		}
		else if (ft_strchr((*token)->token[0], '/') \
			&& !access((*token)->token[0], X_OK))
		{
			ft_putstr_fd(" Is a directory\n", STDERR_FILENO);
			parser()->exit_status = 126;
		}
		perror(" ");
	}
	free_all();
	close(0);
	close(1);
	close(2);
	go_head(token);
	exit(parser()->exit_status);
}
