/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/08/28 16:26:04 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_parsing(char *av, int ac)
{
	int		i;
	char	**line;

	(void)ac;
	tokens()->token = ft_split(av, ' ');
	i = 0;
	line = ft_split(av, ' ');
	while (line[i])
	{
		if (!check_cmds(line, line[i]))
		{
			printf("minishell: command not found: %s\n", line[i]);
			return ;
		}
		return ;
	}
	return ;
}

void	cmd_process(char **av, char **env, int option)
{
	(void)env;
	if (option == 1)
		print_pwd(*av);
	else if (option == 2)
		clr_shell();
	else if (option == 3)
	{
		if (av[1])
			exit(ft_atoi(av[1]));
		else
			exit(0);
	}
	else if (option == 4)
		display_env(tokens()->envp);
	else if (option == 5)
		ft_cd(av);
	else if (option == 6)
		ft_echo(av);
	else if (option == 7)
		ft_export(av);
	else if (option == 8)
		ft_unset(av);
}

int	check_cmds(char **line, char *linei)
{
	if (!ft_strncmp(linei, "pwd", 4))
		cmd_process(line, tokens()->envp, 1);
	else if (!ft_strncmp(linei, "clear", 6) && !linei + 1)
		cmd_process(line, tokens()->envp, 2);
	else if (!ft_strncmp(linei, "exit", 5))
		cmd_process(line, tokens()->envp, 3);
	else if (!ft_strncmp(linei, "env", 4) && !linei + 1)
		cmd_process(line, tokens()->envp, 4);
	else if (!ft_strncmp(linei, "cd", 3))
		cmd_process(line, tokens()->envp, 5);
	else if (!ft_strncmp(linei, "echo", 5))
		cmd_process(line, tokens()->envp, 6);
	else if (!ft_strncmp(linei, "export", 7))
		cmd_process(line, tokens()->envp, 7);
	else if (!ft_strncmp(linei, "unset", 6))
		cmd_process(line, tokens()->envp, 8);
	else
		return (0);
	return (1);
}
