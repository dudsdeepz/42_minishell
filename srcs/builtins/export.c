/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:28:15 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/30 16:27:51 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    display_export(char **env)
{
    int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n",env[i]);
		++i;
	}
	return ;
}

void	ft_export(char **av)
{
	int i;
	char **tmp;
	
	i = 0;
	tmp = NULL;
	if (av[1])
	{
		while (av[++i])
		{
			// if (check_export_str(av[i]))
			// {
			// 	printf("invalid export string: %s\n", av[1]);
			// 	continue ;
			// }
			if (!difs(av[i], '='))
			{
				tmp = ft_split(av[i], '=');
				parser()->envp = send_to_env(tmp[1], parser()->envp, tmp[0]);
				free_matrix(tmp);
			}
			else
				parser()->export_env = send_to_exportenv(av[i], parser()->export_env);
		}
	}
	else
		display_export(parser()->export_env);
	return ;
}

int check_export_Str(char *str)
{
	int i;
	
	i = 0;
	(void)str;
	return (0);
}

char	**send_to_exportenv(char *token, char **env)
{
	int i;
	
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
		env[i] = malloc(sizeof(char *) * ft_strlen(token));
		ft_strcpy(env[i], token);
	}
	else
		env = new_env(token, env);
	return (env);
}

char	**send_to_env(char *token, char **env, char *find)
{
	int i;
	
	i = -1;
	if (!token)
	{
		token = malloc(2);
		token = ft_strdup("""");
	}
	while (env[++i])
	{
		if (!ft_strncmp(find, env[i], ft_strlen(find)))
			break ;
	}
	if (env[i])
	{
		free(env[i]);
		env[i] = malloc(sizeof(char *) * ft_strlen(token) + ft_strlen(find));
		find = ft_strjoin(find, "=");
		ft_strcpy(env[i], ft_strjoin(find, token));
	}
	else
		env = new_env(token, env);
	return (env);
}


char **new_env(char *token, char **env)
{
	char **new;
	int i;
	
	i = 0;
	new = malloc(sizeof(char *) * (list_size(env) + 2));
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strdup(token);
	new[i + 1] = 0;
	free_matrix(env);
	return (new);
}