/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:37:09 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/24 10:43:25 by eduarodr         ###   ########.fr       */
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
		parser()->exit_status = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
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

void	hd_signs(int sig)
{
	if (sig == SIGQUIT)
		SIG_IGN ;
	else if (sig == SIGINT)
	{
		write(2, " ", 1);
		exit(1);
	}
}

void	free_tokens(t_tokens *token)
{
	while (token->prev)
	{
		token = token->prev;
		if (token->token[0] != NULL && token->token)
			free_matrix(token->token);
		free(token->next);
		token->next = NULL;
	}
	free(token);
	token = NULL;
}
