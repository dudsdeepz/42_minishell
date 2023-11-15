/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:26:46 by diomari           #+#    #+#             */
/*   Updated: 2023/11/15 15:56:25 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(void)
{
	int 	i;
	int 	status;
	int 	j;
	pid_t proc;

	i = -1;
	j = 0;
	if (parser()->tokens)
	{
		while (++i < parser()->tokens_n)
		{
			if (parser()->tokens_n == 1)
			{
				one_command(i);
				return ;
			}
			create_pipes();
			if (list_size(parser()->tokens[i].token) > 0)
			{
				if (!check_cmds_(parser()->tokens[i].token))
				{
					proc = fork();
					if (proc == 0)
					{
						if (!ft_strncmp(parser()->signs[i].sign, "|", 1) && i == 0)
							dup2(parser()->tokens[i].fd[1], STDOUT_FILENO);
						signs(parser()->signs[j].sign, i);
						1check_cmds(parser()->tokens[i].token);
						exit(1);
					}
				}
			}
			j++;
		}
		i = 0;
		while (i < parser()->tokens_n)
		{
			waitpid(-1, &status, 0);
				i++;
		}
	}
}

int	signs(char *sign, int tkid)
{
	if ((!ft_strncmp(sign, ">", 1) || !ft_strncmp(sign, "<", 1)))
	{
		redirections(tkid, sign);
		return (tkid);
	}
	if (tkid > 0)
	{
		if (!ft_strncmp(sign, "|", 2))
		{
			pipes(tkid);
			return(tkid);
		}
	}
	return (tkid);
}

int pipes(int tkid)
{
	if (tkid != 0)
		dup2(parser()->tokens[tkid - 1].fd[0], STDIN_FILENO);
	if (tkid != parser()->tokens_n - 1)
	{
		dup2(parser()->tokens[tkid].fd[1], STDOUT_FILENO);
		close(parser()->tokens[tkid].fd[1]);
	}
	close(parser()->tokens[tkid].fd[0]);
	close(parser()->tokens[tkid - 1].fd[1]);
	return (tkid);
}

void	argument(int *fd, char **av, int fd_num, int fd_type)
{
	if (!ft_strncmp(*av, "exit", 4) && list_size(av) == 1)
	{
		check_cmds(av);
		return ;
	}
	if (dup2(fd[fd_num], fd_type) < 0)
		close(fd[fd_num]);
	check_cmds(av);
}

void	exec_system_cmd(char **tokens)
{
	char *getp;
	
	getp = NULL;
	if (ft_strncmp(*tokens, "./", 2))
		getp = get_path(*tokens, parser()->envp);
	if (getp)
	{
		if (execve(getp, tokens, parser()->envp) == -1)
			exit(EXIT_FAILURE);
	}
	free(getp);
	return ;
}


void one_command(int i)
{
	pid_t proc;

	if (!check_cmds_(parser()->tokens[i].token))
	{
		proc = fork();
		if (proc == 0)
			check_cmds(parser()->tokens[i].token);
		else if (proc > 0)
			wait(0) ;
	}
}

void close_fds()
{
	int i;

	i = 0;
	while (i < parser()->tokens_n)
	{
		close(parser()->tokens[i].fd[1]);
		close(parser()->tokens[i].fd[0]);
		i++;
	}
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

void ft_dup(int *fd, int open, int closee, int fd_type)
{
	close(fd[closee]);
	dup2(fd[open], fd_type);
	close(fd[open]);
}

void	create_pipes(void)
{
	int i;

	i = 0;
	while(i < parser()->tokens_n)
	{
		pipe(parser()->tokens[i].fd);
		i++;
	}
}