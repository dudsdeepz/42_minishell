/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:26:46 by diomari           #+#    #+#             */
/*   Updated: 2023/11/14 11:47:06 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(void)
{
	int i;
	int tmp;

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
				i++;
			}
		}
		else
		{
			if (!ft_strncmp(*parser()->tokens[i].token, "exit", 4))
				check_cmds(parser()->tokens[i].token);
			tmp = fork();
			if (tmp == 0)
				check_cmds(parser()->tokens[i].token);
			else if (tmp < 0)
				perror("");
			wait(0);
		}
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
	int tmp_file;
	int id;
	int status;

	pipe(fd);
	while (parser()->signs[tkid])
	{
		id = fork();
		if (id == 0)
		{
			if (!ft_strncmp(parser()->signs[tkid], ">", 1) && parser()->signs[tkid])
			{
				tmp_file = open(*parser()->tokens[tkid + 1].token, O_CREAT | O_RDWR | O_TRUNC, 0644);
				dup2(tmp_file, STDOUT_FILENO);
				argument(fd, parser()->tokens[tkid].token, 0, STDIN_FILENO);
				tkid++;
				break ;
			}
			if (!parser()->signs[tkid + 1])
			{
				argument(fd, parser()->tokens[tkid].token, 0, STDIN_FILENO);
				break ;
			}
			argument(fd, parser()->tokens[tkid].token, 1, STDOUT_FILENO);
		}
		else if (id < 0)
			printf("Error creating command fork!\n");
		tkid++;
		waitpid(id, &status, 0);
	}
	return (tkid + 1);
}

void	exec_system_cmd(char **tokens)
{
	char *getp;
	
	getp = NULL;
	if (ft_strncmp(*tokens, "./", 2))
		getp = get_path(*tokens, parser()->envp);
	if (getp)
		execve(getp, tokens, parser()->envp);
	free(getp);
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

void	argument(int *fd, char **av, int fd_num, int fd_type)
{
	if (!ft_strncmp(*av, "exit", 4) && list_size(av) == 1)
	{
		check_cmds(av);
		return ;
	}
	if (fd_num != 0 && dup2(fd[fd_num], fd_type) < 0)
		close(fd[fd_num]);
	check_cmds(av);
}