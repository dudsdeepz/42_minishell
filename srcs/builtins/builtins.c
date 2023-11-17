/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:48:45 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/16 20:45:57 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_pwd(char *av)
{
	char	*cwd;

	//done, need to remove av
	(void)av;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

void	display_env(char **env)
{
	//done
	int	i;

	i = 0;
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


int	exec_cmds(char **linei)
{
	if (linei[0] && !ft_strncmp(linei[0], "pwd", 4))
		print_pwd(*linei);
	else if (linei[0] && !ft_strncmp(linei[0], "env", 4) && !linei[1])
		display_env(parser()->envp);
	else if (linei[0] && !ft_strncmp(linei[0], "echo", 5))
		ft_echo(linei);
	else if (linei[0] && !ft_strncmp(linei[0], "exit", 5))
		ft_exit(linei);
		else if (linei[0] && !ft_strncmp(linei[0], "cd", 3))
		ft_cd(linei);
	else if (linei[0] && !ft_strncmp(linei[0], "export", 7))
		ft_export(linei);
	else if (linei[0] && !ft_strncmp(linei[0], "unset", 6))
		ft_unset(linei);
	else
		return (0);
	return (1);
}

void	ft_exec(char **token)
{
	char *path;
	
	path = NULL;
	if (!check_built(token))
		path = get_path(*token, parser()->envp);
	if (path)
		execve(path, token, parser()->envp);
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