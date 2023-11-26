/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:15:25 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/26 16:36:21 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**new_env_unset(char *token, char **env)
{
	int	i;
	int	a;

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
	free_matrix(env);
	return (dup_matrix(parser()->tmp_matrix));
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
	close_fds(token, 0);
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
}

char	**env_help(char **env, char *token, char *find)
{
	env = new_env(token, env, ft_strjoin(find, "="));
	free_matrix(parser()->tmp_matrix);
	return (env);
}
