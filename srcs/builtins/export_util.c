/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:33:46 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/24 12:11:23 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**send_to_env(char *token, char **env, char *find)
{
	int		i;
	char	*str;

	i = -1;
	if (!token)
		token = "\0";
	while (env[++i])
	{
		if (!ft_strncmp(find, env[i], ft_strlen(find)))
			break ;
	}
	if (env[i])
	{
		free(env[i]);
		find = ft_strjoin(find, "=");
		str = ft_strjoin(find, token);
		free(find);
		env[i] = ft_strdup(str);
		free(str);
	}
	else
		env = env_help(env, token, find);
	return (env);
}

char	**new_env(char *token, char **env, char *find)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = 0;
	parser()->tmp_matrix = malloc(sizeof(char *) * (list_size(env) + 2));
	while (env[i] != 0)
	{
		parser()->tmp_matrix[i] = ft_strdup(env[i]);
		i++;
	}
	if (find)
	{
		tmp = ft_strjoin(find, token);
		parser()->tmp_matrix[i] = ft_strdup(tmp);
		free(tmp);
		free(find);
		find = NULL;
		tmp = NULL;
	}
	else
		parser()->tmp_matrix[i] = ft_strdup(token);
	parser()->tmp_matrix[i + 1] = 0;
	free_matrix(env);
	return (dup_matrix(parser()->tmp_matrix));
}

void	export_util(char *str, char **tmp)
{
	char	**tmp1;
	char	**tmp2;

	tmp1 = send_to_env(tmp[1], parser()->envp, str);
	parser()->envp = tmp1;
	tmp2 = send_to_env(tmp[1], parser()->export_env, str);
	parser()->export_env = tmp2;
}

char	**send_to_exportenv(char *token, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(token, env[i], ft_strlen(token)))
			break ;
		i++;
	}
	if (env[i])
	{
		free(env[i]);
		env[i] = ft_strdup(token);
	}
	else
	{
		env = new_env(token, env, NULL);
		free_matrix(parser()->tmp_matrix);
	}
	return (env);
}
