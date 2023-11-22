/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:15:25 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 17:45:48 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **new_env_unset(char *token, char **env)

{
	int i;
	int a;
	
	i = 0;
	a = 0;
	parser()->tmp_matrix = malloc(sizeof(char *) * list_size(env) + 1);
	while (env[a++])
	{
		if (env[a] && !ft_strncmp(token, env[a], ft_strlen(token)))
			a++;
		if (env[a])
			parser()->tmp_matrix[i++] = ft_strdup(env[a]);
	}
	parser()->tmp_matrix[i] = 0;
	if (env != NULL)
		free_matrix(env);
	return (dup_matrix(parser()->tmp_matrix));
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
				free_matrix(tmp);
			}
			else
				unset_uti((*token)->token[i]);
		}
	}
	return ;
}


void	unset_uti(char *str)
{
	parser()->envp = new_env_unset(str, parser()->envp);
	free_matrix(parser()->tmp_matrix);
	parser()->export_env = new_env_unset(str, parser()->export_env);
	free_matrix(parser()->tmp_matrix);
}