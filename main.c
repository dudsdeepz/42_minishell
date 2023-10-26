/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/25 14:45:53 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cwd;
	char	*line;

	(void)av;
	if (ac == 1)
	{
		line = 0;
		parser()->heredoc = malloc(sizeof(t_heredoc));
		parser()->envp = dup_matrix(env);
		parser()->heredoc->h_content = NULL;
		parser()->heredoc->in_heredoc = 0;
		sig_actions();
		while (1)
		{
			if (!parser()->heredoc->in_heredoc)
			{
				cwd = readline("minishell: ");
				if (!cwd)
					return (0);
				if (cwd && !ft_strncmp(cwd, "<<", 3))
				{
					parser()->heredoc->in_heredoc = 1;
					parser()->heredoc->h_content = ft_strdup("");
					continue ;
				}
				if (ft_strlen(cwd) > 0)
					shell(cwd);
			}
			else
			{
				line[ft_strcspn(line, "\n")] = '\0';
				if (ft_strncmp(line, "EOF", 4) == 0)
					parser()->heredoc->in_heredoc = 0;
				else
					p_heredoc(line);
			}
		}
		free_heredoc(parser()->heredoc->h_content);
	}
	return (0);
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
			expansion();
			executor();
		}
	}
	free(cwd);
}