/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:15:25 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/06 15:27:01 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **new_env_unset(char *token, char **env)

{
	char **new;
	int i;
	
	i = 0;
	int a = 0;
	new = malloc(sizeof(char *) * (list_size(env)));
	while (env[a++])
	{
		if (env[a] && !ft_strncmp(token, env[a], ft_strlen(token)))
			a++;
		if (env[a])
			new[i++] = ft_strdup(env[a]);
	}
	new[i] = 0;
	free_matrix(env);
	return (new);
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
				parser()->envp = new_env_unset(tmp[0], parser()->envp);
				parser()->export_env = new_env_unset(tmp[0], parser()->export_env);
				free_matrix(tmp);
			}
			else
			{
				parser()->envp = new_env_unset(av[i], parser()->envp);
				parser()->export_env = new_env_unset(av[i], parser()->export_env);
			}
		}
	}
	return ;
}
