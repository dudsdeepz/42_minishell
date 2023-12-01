/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:15:25 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 10:33:16 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**new_env_unset(char *token, char **env)
{
	int		i;
	int		a;
	char	**tmp;

	i = 0;
	a = -1;
	parser()->tmp_matrix = malloc(sizeof(char *) * (list_size(env) + 2));
	while (env[++a])
	{
		tmp = ft_split(env[a], '=');
		if (env[a] && (!ft_strcmp(token, tmp[0]) || !ft_strcmp(token, env[a])))
		{
			free_matrix(tmp);
			continue ;
		}
		free_matrix(tmp);
		if (env[a])
			parser()->tmp_matrix[i++] = ft_strdup(env[a]);
	}
	parser()->tmp_matrix[i] = 0;
	free_matrix(env);
	env = dup_matrix(parser()->tmp_matrix);
	return (env);
}

void	unset_uti(char *str)
{
	char	**tmp;
	char	**tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = new_env_unset(str, parser()->envp);
	parser()->envp = tmp;
	free_matrix(parser()->tmp_matrix);
	tmp2 = new_env_unset(str, parser()->export_env);
	parser()->export_env = tmp2;
	free_matrix(parser()->tmp_matrix);
}

void	_ft_unset(t_tokens **token)
{
	int		i;
	char	**tmp;

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
			unset_uti((*token)->token[i]);
		}
	}
	parser()->exit_status = 0;
}

char	**env_help(char **env, char *find)
{
	env = new_env(env, find);
	free_matrix(parser()->tmp_matrix);
	return (env);
}
