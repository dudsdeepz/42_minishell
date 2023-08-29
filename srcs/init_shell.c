/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:37:09 by eduarodr          #+#    #+#             */
/*   Updated: 2023/08/28 16:20:16 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	loop_pwd(char *str)
{
	char	*cwd;
	char	*username;
	char	*pc_name;
	char	*shell;

	username = getenv("USER");
	pc_name = getenv("NAME");
	shell = get_shell_prompt(username, pc_name);
	cwd = readline(shell);
	if (ft_strlen(cwd) != 0 && cwd)
	{
		add_history(cwd);
		ft_strcpy(str, cwd);
		return (0);
	}
	else
		return (1);
}

int	ft_strcpy(char *dst, char *src)
{
	int		i;
	int		srclen;

	srclen = ft_strlen(src);
	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		exit(0);
	}
}

char *get_shell_prompt(char *username, char *pc_name)
{
	char	*first;
	char	*second;

	first = ft_strjoin(username, "@");
	second = ft_strjoin(first, pc_name);
	return (ft_strjoin(second, ": "));
}

void	sig_actions(void)
{
	signal(SIGINT, handle_signals);
	if (signal(SIGQUIT, handle_signals))
		exit(0);
}