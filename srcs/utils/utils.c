/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:05:12 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 10:06:06 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_putstr(char *str, char *color)
{
	int i = 0;
	int j = 0;

	if (color)
	{
		while (color[i])
		{
			write(1, &color[i], 1);
			i++;
		}
	}
	if (str)
	{
		while (str[j])
		{
			write(1, &str[j], 1);
			j++;
		}
	}
	return (str);
}

t_parser	*parser(void)
{
	static t_parser	parser;

	return (&parser);
}

char	*get_path(char *command, char **env)
{
	int		i;
	char	**path;
	char	*str;
	char 	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break;
		i++;
	}
	if (!env[i] || ft_strlen(env[i]) < 6)
	{
		printf("path not found !\n");
		return ("\0");
	}
	path = ft_split(env[i] + 5, ':');
	i = 0;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	while (path[i])
	{
		str = triple_strjoin(path[i++], "/", command);
		if (!access(str, F_OK))
			break ;
		free(str);
		str = NULL;
	}
	free_matrix(path);
	if (!str)
	{
		free(str);
		str = NULL;
		printf("%sCommand not found: %s ! %s\n", RED, command, DEFAULT);
		parser()->exit_status = 127;
		return ("\0");
	}
	tmp = ft_strdup(str);
	free(str);
	str = NULL;
	return (tmp);
}