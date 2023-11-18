/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/18 19:54:34 by eduarodr         ###   ########.fr       */
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
				shell(cwd);
			else
				free(cwd);
		}
	}
	free(cwd);
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
	parser()->tokens = (t_tokens *)malloc(sizeof(t_tokens *));
	parser()->global_error = 0;
	add_history(cwd);
	cwd = get_prompt(cwd, malloc(ft_strlen(cwd) * 5));
	if (cwd)
	{
		if (parsing(cwd))
		{
			if (!!parser()->global_error)
				get_tokens(cwd, &parser()->tokens);
			if (!parser()->global_error)
				executor(parser()->tokens);
			parser()->global_error = 0;
		}
	}
	free(cwd);
}