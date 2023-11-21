/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:48:45 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/21 10:34:19 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_ft_pwd(t_tokens **token)
{
	char	*cwd;

	(void)token;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void	_ft_env(t_tokens **token)
{
	char **env;
	int	i;

	i = 0;
	(void)token;
	env = parser()->envp;
	while (env[i])
	{
		printf("%s\n",env[i]);
		++i;
	}
	return ;
}

void	free_matrix(char **mtx)
{
	int	p;

	p = 0;
	if (list_size(mtx) > 0)
	{
		while (mtx[p])
		{
			if (mtx[p])
				free(mtx[p]);
			p++;
		}
		free(mtx);
	}
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
	if (linei[0] && !ft_strncmp(linei[0], "pwd", 4))
		return (1);
	else if (linei[0] && !ft_strncmp(linei[0], "env", 4) && !linei[1])
		return (1);
	else if (linei[0] && !ft_strncmp(linei[0], "echo", 5))
		return (1);
	else if (linei[0] && !ft_strncmp(linei[0], "exit", 5))
		return (1);
	else if (linei[0] && !ft_strncmp(linei[0], "cd", 3))
		return (1);
	else if (linei[0] && !ft_strncmp(linei[0], "export", 7))
		return (1);
	else if (linei[0] && !ft_strncmp(linei[0], "unset", 6))
		return (1);
	return (0);
}

void _ft_exec_cmd(t_tokens **token)
{
	close_fds(token, 1);
	execve((*token)->path, (*token)->token, parser()->envp) ;
	close(0);
	close(1);
	go_head(token);
	exit(parser()->exit_status);
}