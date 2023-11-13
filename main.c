/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/13 12:12:13 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cwd;
	char	*line;

	(void)av;
	cwd = NULL;
	if (ac == 1)
	{
		line = 0;
		parser()->heredoc = malloc(sizeof(t_heredoc));
		parser()->envp = dup_matrix(env);
		parser()->export_env = dup_matrix(env);
		parser()->heredoc->h_content = NULL;
		parser()->heredoc->in_heredoc = 0;
		sig_actions();
		while (1)
		{
			if (!parser()->heredoc->in_heredoc)
			{
				cwd = readline("m1n1sh1t: ");
				if (!cwd)
				{
					return (0);
				}
				if (cwd && !ft_strncmp(cwd, "<<", 3))
				{
					parser()->heredoc->in_heredoc = 1;
					parser()->heredoc->h_content = ft_strdup("");
					continue ;
				}
				if (ft_strlen(cwd) > 0)
					shell(cwd);
				else
					free(cwd);
			}
			else
			{
				line[ft_strcspn(line, "\n")] = '\0';
				if (ft_strncmp(line, "EOF", 4) == 0)
					parser()->heredoc->in_heredoc = 0;
				else
					p_heredoc(line);
			}
		}
		free_heredoc(parser()->heredoc->h_content);
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
	add_history(cwd);
	cwd = get_prompt(cwd, malloc(ft_strlen(cwd) * 5));
	if (cwd)
	{
		if (parsing(cwd))
		{
			get_tokens(cwd);
			expansion();
			executor();
			free_tokens();
		}
	}
	free(cwd);
}