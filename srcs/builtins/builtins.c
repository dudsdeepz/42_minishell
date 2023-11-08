/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:48:45 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/08 15:53:35 by eduarodr         ###   ########.fr       */
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
	if (mtx)
	{
		while (mtx[p])
			free(mtx[p++]);
		free(mtx);
	}
}


int	check_cmds(char **linei)
{
	if (!ft_strncmp(linei[0], "pwd", 4))
		print_pwd(*linei);
	else if (!ft_strncmp(linei[0], "exit", 5))
		ft_exit(linei);
	else if (!ft_strncmp(linei[0], "env", 4) && !linei[1])
		display_env(parser()->envp);
	else if (!ft_strncmp(linei[0], "cd", 3))
		ft_cd(linei);
	else if (!ft_strncmp(linei[0], "echo", 5))
		ft_echo(linei);
	else if (!ft_strncmp(linei[0], "export", 7))
		ft_export(linei);
	else if (!ft_strncmp(linei[0], "unset", 6))
		ft_unset(linei);
	else
		return (0);
	return (1);
}
