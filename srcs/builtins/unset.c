/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:15:25 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/29 12:31:40 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**new_env_unset(char *token, char **env)
{
	int	i;
	int	a;
	char **tmp;
	
	i = 0;
	a = -1;
	(void)token;
	parser()->tmp_matrix = malloc(sizeof(char *) * list_size(env));
	while (env[++a])
	{
		tmp = ft_split(env[i], '=');
		if (env[a] && !ft_strcmp(token, tmp[0]))
		{
			free_matrix(tmp);
			continue ;
		}
		free_matrix(tmp);
		// if (env[a])
		parser()->tmp_matrix[i++] = ft_strdup(env[a]);
	}
	parser()->tmp_matrix[--i] = 0;
	free_matrix(env);
	return (dup_matrix(parser()->tmp_matrix));
}

void	unset_uti(char *str)
{
	char	**tmp;
	char	**tmp2;
	

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
			unset_uti((*token)->token[i]);
		}
	}
}

char	**env_help(char **env, char *find)
{
	env = new_env(env, find);
	free_matrix(parser()->tmp_matrix);
	return (env);
}
