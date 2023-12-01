/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:33:46 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 10:38:03 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**send_to_env(char **env, char *find)
{
	int		i;
	char	**str;
	char	**tmp;

	i = -1;
	if (!find)
		find = "\0";
	while (env[++i])
	{
		tmp = ft_split(find, '=');
		str = ft_split(env[i], '=');
		if (!ft_strcmp(str[0], tmp[0]))
		{
			free_matrix(str);
			free_matrix(tmp);
			break ;
		}
		free_matrix(tmp);
		free_matrix(str);
	}
	if (env[i])
		env[i] = aux_envi(env[i], find);
	else
		env = env_help(env, find);
	return (env);
}

char	**new_env(char **env, char *find)
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
	parser()->tmp_matrix[i] = ft_strdup(find);
	parser()->tmp_matrix[++i] = 0;
	free_matrix(env);
	env = dup_matrix(parser()->tmp_matrix);
	return (env);
}

void	export_util(char *str)
{
	char	**tmp1;
	char	**tmp2;

	tmp1 = send_to_env(parser()->envp, str);
	parser()->envp = tmp1;
	tmp2 = send_to_env(parser()->export_env, str);
	parser()->export_env = tmp2;
}

char	**send_to_exportenv(char *token, char **env)
{
	int		i;
	char	**tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_split(env[i], '=');
		if (!ft_strcmp(token, tmp[0]))
		{
			free_matrix(tmp);
			return (env);
		}
		free_matrix(tmp);
	}
	env = new_env(env, token);
	free_matrix(parser()->tmp_matrix);
	return (env);
}

char	*file_quotes(char *str)
{
	char	*tmp;

	tmp = ft_strdup(str);
	free(str);
	str = NULL;
	str = remove_quotes(tmp);
	free(tmp);
	tmp = NULL;
	return (str);
}
