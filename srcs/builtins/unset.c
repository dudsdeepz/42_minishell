/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:15:25 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/20 21:27:48 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **new_env_unset(char *token, char **env)

{
	char **new;
	int i;
	int a;
	
	i = 0;
	a = 0;
	new = malloc(sizeof(char *) * list_size(env) + 1);
	while (env[a++])
	{
		if (env[a] && !ft_strncmp(token, env[a], ft_strlen(token)))
			a++;
		if (env[a])
			new[i++] = ft_strdup(env[a]);
	}
	new[i] = 0;
	// free_matrix(env);
	return (new);
}

void	_ft_unset(t_tokens **token)
{
	int i;
	char **tmp;

	i = 0;
	tmp = NULL;
	if ((*token)->token[1])
	{
		while ((*token)->token[++i])
		{
			if (check_export_str((*token)->token[i]))
			{
				printf("invalid unset string: %s\n", (*token)->token[i]);
				continue ;
			}
			if (!difs((*token)->token[i], '='))
			{
				tmp = ft_split((*token)->token[i], '=');
				unset_uti(tmp[0]);
				free_path(tmp);
			}
			else
				unset_uti((*token)->token[i]);
		}
	}
	return ;
}


void	unset_uti(char *str)
{
	parser()->envp = dup_matrix(new_env_unset(str, parser()->envp));
	parser()->export_env = dup_matrix(new_env_unset(str, parser()->export_env));
}