/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:39:51 by diomari           #+#    #+#             */
/*   Updated: 2023/11/13 16:17:53 by eduarodr         ###   ########.fr       */
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
	if (!ft_strncmp(av[i], ">", 1))
		return (1);
	while (ft_strncmp(av[i], ">", 1))
		i++;
	if (av[i])
		return (i);
	else
		return (0);
}

int redirections(int tkid, int i, char **av)
{
	// int file;
	// int fd[2];

	// pipe(fd);
	while (av[i] || !ft_strncmp(av[i], "|", 1))
		i--;
	// print_dp(parser()->tokens[tkid].token);
	// while (ft_strncmp(av[i], ">", 1))
	// {
	// 	parser()->tokens[tkid].token_fork = fork();
	// 	if (parser()->tokens[tkid].token_fork == 0)
	// 		argument(fd, parser()->tokens[tkid].token, STDOUT_FILENO);
	// 	else if (parser()->tokens[tkid].token_fork < 0)
	// 		printf("Error creating fork !\n");
	// 	wait(0);
	// 	tkid++;
	// 	i++;
	// }
	// while (av[i] && !ft_strncmp(av[i], ">", 1))
	// {
	// 	file = open(*parser()->tokens[tkid + 1].token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	// 	dup2(file, STDOUT_FILENO);
	// 	i++;
	// 	tkid++;
	// }
	(void)tkid;
	return (i);
}