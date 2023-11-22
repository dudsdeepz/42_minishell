/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:37:09 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 10:15:10 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_shell(void)
{
	char	*username;
	char	*pc_name;

	pc_name = getenv("NAME");
	username = getenv("USER");
	printf("\n%sUSER: %s%s\n%sDEVICE NAME: %s%s\n", YELLOW, DEFAULT, username, \
		YELLOW, DEFAULT, pc_name);
	printf("%s===================%s\n", WHITE, DEFAULT);
}
void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		free_envs();
		exit(0);
	}
}

char	*get_shell_prompt(char *username, char *pc_name)
{
	char	*first;
	char	*second;

	first = ft_strjoin(username, "@");
	second = ft_strjoin(first, pc_name);
	return (ft_strjoin(second, ": "));
}
