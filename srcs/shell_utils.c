/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/09/06 16:34:30 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void get_tokens(char *cwd)
{
	char **new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = ft_split(cwd, ' ');
	while (new[i])
	{
		while (new[i][j] != 0) 
			j++;
		new[i][j] = '\0';
		j = 0;
		i++;
	}
	tokens()->token = new;
}