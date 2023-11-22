/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 10:22:38 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cwd;

	(void)av;
	cwd = NULL;
	if (ac == 1)
	{
		sig_actions();
		parser()->envp = dup_matrix(env);
		parser()->export_env = dup_matrix(env);
		while (1)
		{
			cwd = readline("minishell: ");
			if (!cwd)
				return (0);
			if (ft_strlen(cwd) > 0)
			{
				add_history(cwd);
				shell(cwd);
			}
		}
	}
	return (0);
}

int	list_size(char **list)
{
	int i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}


void shell(char *cwd)
{
	char *tmp;
	
	tmp = get_prompt(cwd, malloc(ft_strlen(cwd) * 5));
	if (tmp)
		if (parsing(tmp))
			shell_output(tmp);
	free(tmp);
}

int	ft_heredoc(char *a)
{
	printf("heredoc: char: %s\n", a);
	return (0);
	(void)a;
}