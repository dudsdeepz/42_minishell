/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:15:25 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/10 09:41:15 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **new_env_unset(char *token, char **env)

{
	// char **new;
	int i;
	int a;
	
	i = 0;
	a = 0;
	parser()->tmp_matrix = malloc(sizeof(char *) * list_size(env));
	while (env[a] != 0)
	{
		if (env[a] && !ft_strncmp(token, env[a], ft_strlen(token)))
			a++;
		if (env[a])
		{
			parser()->tmp_matrix[i] = ft_strdup(env[a]);
			i++;
		}
		a++;
	}
	parser()->tmp_matrix[i] = 0;
	free_matrix(env);
	return (parser()->tmp_matrix);
}

void	ft_unset(char **av)
{
	int i;
	char **tmp;

	i = 0;
	tmp = NULL;
	if (av[1])
	{
		while (av[++i])
		{
			if (check_export_str(av[i]))
			{
				printf("invalid unset string: %s\n", av[i]);
				continue ;
			}
			if (!difs(av[i], '='))
			{
				tmp = ft_split(av[i], '=');
				unset_uti(tmp[0]);
				free_path(tmp);
			}
			else
				unset_uti(av[i]);
		}
	}
	return ;
}


void	unset_uti(char *str)
{
	parser()->envp = new_env_unset(str, parser()->envp);
	parser()->export_env = new_env_unset(str, parser()->export_env);
	free_matrix(parser()->tmp_matrix);
}