/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:39:51 by diomari           #+#    #+#             */
/*   Updated: 2023/11/15 15:31:55 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void check_red()
{
	// int input_red = 0;
	// int output_red = 0;
	
}

int	check_redir(char **av, int i)
{
	if (av[i] && (!ft_strncmp(av[i], ">", 1) || !ft_strncmp(av[i], "<", 1)))
		return (1);
	while (av[i] && (!ft_strncmp(av[i], ">", 1) || !ft_strncmp(av[i], "<", 1)))
		i++;
	if (av[i])
		return (i);
	else
		return (0);
}

int redirections(int tkid, char *av)
{
	int file;

	file = 0;
	
	if (!ft_strncmp(av, ">", 1))
	{
		file = open(*parser()->tokens[tkid + 1].token, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(file, STDOUT_FILENO);
		dup2(parser()->tokens[tkid].fd[0], STDIN_FILENO);
	}
	if (!ft_strncmp(av, "<", 1))
	{
		file = open(*parser()->tokens[tkid + 1].token, O_RDONLY);
		dup2(file, STDIN_FILENO);
		dup2(parser()->tokens[tkid].fd[1], STDOUT_FILENO);
	}
	close(file);
	return (1);
}