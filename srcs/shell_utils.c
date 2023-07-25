/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/25 17:57:59 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_parsing(char *av, int ac)
{
	int		i;
	char	**line;

	(void)ac;
	i = 0;
	line = ft_split(av, ' ');
	while (line[i])
	{
		if (!ft_strncmp(line[i], "pwd", 4))
		{
			if (print_pwd(av))
				return ;
		}
		else if (!ft_strncmp(line[i], "clear", 6))
			clr_shell(av);
		else if (!ft_strncmp(line[i], "exit", 5))
			exit(1);
		else
		{
			printf("minishell: command not found: %s\n", line[i]);
			return ;
		}
		++i;
	}
	return ;
}

void	cmd_process(char **av)
{
	(void)av;
	return ;
}

int	print_pwd(char *av)
{
	char	cwd[1024];
	int		i;
	char	**line;

	i = 0;
	line = ft_split(av, ' ');
	while (line[i])
		i++;
	if (i > 1)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (0);
}

void	clr_shell(char *str)
{
	const char	*clear = "\e[1;1H\e[2J";

	(void)str;
	write(STDOUT_FILENO, clear, 11);
}
