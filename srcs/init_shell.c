/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:37:09 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/25 17:39:03 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(void)
{
	char	*username;
	char	*pc_name;

	pc_name = getenv("NAME");
	username = getenv("USER");
	printf("%sUSER: %s%s\n%sDEVICE NAME: %s%s\n", YELLOW, DEFAULT, username, \
		YELLOW, DEFAULT, pc_name);
	printf("%s===================%s\n", WHITE, DEFAULT);
}

int	loop_pwd(char *str)
{
	char	*cwd;
	char	*username;
	char	*pc_name;

	username = getenv("USER");
	pc_name = getenv("NAME");
	printf("%s%s%s@%s%s%s", RED, username, WHITE, BLUE, pc_name, DEFAULT);
	cwd = readline(":");
	if (ft_strlen(cwd) != 0)
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
