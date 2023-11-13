/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:26:46 by diomari           #+#    #+#             */
/*   Updated: 2023/11/13 17:23:42 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(void)
{
	int i;

	i = 0;
	if (parser()->tokens)
	{
		if (parser()->tokens_n > 1)
		{
			while (i < parser()->tokens_n)
			{
				// if (check_redir(parser()->signs, i))
				// 	i = redirections(i, i, parser()->signs);	
				if (parser()->signs[i] && !ft_strncmp(parser()->signs[i], "|", 1))
					i = pipes(i);
				wait(0);
				i++;
			}
		}
		else
			check_type(parser()->tokens[i].token, i);
	}
}

void p_heredoc(char *line)
{
	char *new_content;

	new_content = malloc(ft_strlen(parser()->heredoc->h_content) + ft_strlen(line) + 2);
	ft_strcpy(new_content, parser()->heredoc->h_content);
	ft_strcat(new_content, line);
	ft_strcat(new_content, "\n");
	free(parser()->heredoc->h_content);
	parser()->heredoc->h_content = new_content;
}

int pipes(int tkid)
{
	int fd[2];

	pipe(fd);
	while ((parser()->signs[tkid] && !ft_strncmp(parser()->signs[tkid], "|", 1)))
	{
		if (check_cmds(parser()->tokens[tkid].token))
		{
			tkid++;
			continue ;
		}
		parser()->tokens[tkid].token_fork = fork();
		if (parser()->tokens[tkid].token_fork == 0)
			argument(fd, parser()->tokens[tkid].token, STDOUT_FILENO, 1);
		else if (parser()->tokens[tkid].token_fork < 0)
			printf("Error creating fork !\n");
		wait(0);
		tkid++;
	}
	parser()->tokens[tkid].token_fork = fork();
	if (parser()->tokens[tkid].token_fork == 0)
		argument(fd, parser()->tokens[tkid].token, STDIN_FILENO, 0);
	else if (parser()->tokens[tkid].token_fork < 0)
		printf("Error creating fork !\n");
	return (tkid);
}

void	exec_system_cmd(char **tokens, int tkid)
{
	char *getp;
	
	getp = NULL;
	parser()->tokens[tkid].token_fork = fork();
	if (parser()->tokens[tkid].token_fork < 0)
		exit(write(1, "\e[0;31m Error creating fork!\e[0;31m", 36));
	if (ft_strncmp(*tokens, "./", 2))
		getp = get_path(*tokens, parser()->envp);
	if (parser()->tokens[tkid].token_fork == 0 && *tokens)
	{
		if (!ft_strncmp(*tokens, "exit", 4))
			return ;
		execve(getp, tokens, parser()->envp);
	}
	free(getp);
	wait(0);
	return ;
}

void	close_all(int *fd, int i, char *getp, char **comand)
{
	free(getp);
	free_path(comand);
	close(fd[i]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(1);
}

void	argument(int *fd, char **av, int fd_type, int fd_num)
{
	char	*getp;

	getp = NULL;
	if (ft_strncmp(*av, "./", 2))
		getp = get_path(*av, parser()->envp);
	if (dup2(fd[fd_num], fd_type) < 0)
		close(fd[fd_num]);
	if (getp)
		execve(getp, av, parser()->envp);
}

void	check_type(char **token, int tkid)
{
	if (!check_cmds(token))
		exec_system_cmd(token, tkid);
}

