/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:28:15 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/21 09:25:45 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    display_export(char **env)
{
    int	i;
	int a;
	int checker;

	i = 0;
	while (env[i])
	{
		a = 0;
		checker = 0;
		ft_putstr("declare -x ", 0);
		while (env[i][a])
		{
			write(1, &env[i][a++], 1);
			if (!checker && env[i][a - 1] == '=')
			{
				write(1, "\"", 2);
				checker++;
			}
		}
		if (checker)
			write(1, "\"", 2);
		write(1, "\n", 2);
		i++;
	}
	return ;
}

void	_ft_export(t_tokens **token)
{
	int i;
	char **tmp;

	i = 0;
	if ((*token)->token[1])
	{
		while ((*token)->token[++i])
		{
			if (check_export_str((*token)->token[i]))
			{
				printf("invalid export string: %s\n", (*token)->token[i]);
				continue ;
			}
			if (!difs((*token)->token[i], '='))
			{
				tmp = ft_split((*token)->token[i], '=');
				export_util(tmp[0], tmp);
				free_matrix(tmp);
			}
			else
				parser()->export_env = send_to_exportenv((*token)->token[i], parser()->export_env);
		}
	}
	else
		display_export(parser()->export_env);
	return ;
}

int check_export_str(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]) || !ft_isalpha(str[i]))
		return(1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**send_to_exportenv(char *token, char **env)
{
	int i;
	char **tmp;

	i = 0;
	tmp = dup_matrix(env);
	free_matrix(env);
	while (tmp[i])
	{
		if (!ft_strncmp(token, tmp[i], ft_strlen(token)))
			break ;
		i++;
	}
	if (tmp[i])
	{
		free(tmp[i]);
		tmp[i] = ft_strdup(token);
	}
	else
		tmp = new_env(token, tmp, NULL);
	return (tmp);
}

char	**send_to_env(char *token, char **env, char *find)
{
	int i;
	char *str;
	
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
		env = new_env(token, env, ft_strjoin(find, "="));
	return (env);
}

char **new_env(char *token, char **env, char *find)
{
	char **new;
	int i;
	
	i = 0;
	new = malloc(sizeof(char *) * (list_size(env) + 2));
	while (env[i] != 0)
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	if (find)
		token = ft_strjoin(find, token);
	free(find);
	new[i] = ft_strdup(token);
	new[i + 1] = 0;
	free_matrix(env);
	return (new);
}


void export_util(char *str, char **tmp)
{
	parser()->envp = send_to_env(tmp[1], parser()->envp, str);
	parser()->export_env = send_to_env(tmp[1], parser()->export_env, str);
}
