/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/11 14:42:43 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cwd;

	(void)av;
	tokens()->envp = dup_matrix(env);
	if (ac == 1)
	{
		sig_actions();
		while (1)
		{
			cwd = readline("minishell: ");
			if (!cwd)
				return (0); // exit
			if (ft_strlen(cwd) > 0)
			{
				add_history(cwd);
				cwd = get_prompt(cwd, malloc(ft_strlen(cwd) * 5));
				if (cwd)
				{
					if (parsing(cwd))
					{
						get_tokens(cwd);
						// executor();
					}
				}
			}
			free(cwd);
		}
	}
	return (0);
}

void	executor(void)
{
	int i;
	char **arg;

	i = 0;
	arg = ft_split(tokens()->token[i], '\2');
	check_cmds(tokens()->token[i]);
		// exec_system_cmd(arg, tokens()->envp);
}

int	list_size(char **list)
{
	int i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

void	exec_system_cmd(char **tokens, char **env)
{
	char *getp;
	// int fd[2];
	int id;
	int i;

	i = 0;
	getp = 0;
	// pipe(fd);
	id = fork();
	if (id < 0)
		exit(write(1, "\e[0;31m Error creating fork!\e[0;31m", 36));
	if (id == 0)
		getp = get_path(tokens[i], env);
	execve(getp, tokens, env);
	wait(0);
	free(getp);
	return ;
}
