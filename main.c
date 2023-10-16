/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/16 15:18:23 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cwd;

	(void)av;
	parser()->envp = dup_matrix(env);
	if (ac == 1)
	{
		sig_actions();
		while (1)
		{
			cwd = readline("minishell: ");
			if (!cwd)
				return (0);
			if (ft_strlen(cwd) > 0)
				shell(cwd);
		}
	}
	return (0);
}

void	executor(void)
{
	int i;

	i = 0;
	while (i < parser()->tokens_n)
	{
		if (!(check_cmds(parser()->tokens[i].token)))
			exec_system_cmd(parser()->tokens[i].token, parser()->envp, i);
		i++;
	}
}

int	list_size(char **list)
{
	int i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

void	exec_system_cmd(char **tokens, char **env, int tkid)
{
	char *getp;
	int fd[2];
	int i;

	i = 0;
	getp = 0;
	pipe(fd);
	parser()->tokens[tkid].token_fork = fork();
	if (parser()->tokens[tkid].token_fork < 0)
		exit(write(1, "\e[0;31m Error creating fork!\e[0;31m", 36));
	if (parser()->tokens[tkid].token_fork == 0)
		getp = get_path(tokens[i], env);
	execve(getp, tokens, env);
	wait(0);
	free(getp);
	return ;
}

void shell(char *cwd)
{
	add_history(cwd);
	cwd = get_prompt(cwd, malloc(ft_strlen(cwd) * 5));
	if (cwd)
	{
		if (parsing(cwd))
		{
			get_tokens(cwd);
			executor();
		}
	}
	free(cwd);
}