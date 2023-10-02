/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:05:12 by eduarodr          #+#    #+#             */
/*   Updated: 2023/09/27 17:54:22 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_tokens	*tokens(void)
{
	static t_tokens	tokens;

	return (&tokens);
}

char *ft_strremove(char *substr) 
{
    size_t i;

	i = 0;
	while (substr[i] != 0)
	{
		i++;
		substr[i - 1] = '\0';
	}
	substr[i] -= 1;
    return (substr);
}

char	*get_path(char *command, char **env)
{
	int		i;
	char	**path;
	char	*str;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		str = triple_strjoin(path[i++], "/", command);
		if (!access(str, F_OK))
			break ;
		free(str);
		str = NULL;
	}
	if (!str)
	{
		printf("%sCommand not found !%s\n", RED, DEFAULT);
		strerror(1);
		exit(0);
	}
	free_path(path);
	return (str);
}

void	free_path(char **list)
{
	int	i;

	if (list)
	{
		i = 0;
		while (list[i])
			free(list[i++]);
		free(list);
	}
}

char	*triple_strjoin(char *s1, char *s2, char *s3)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	while (*s3)
		res[i++] = *s3++;
	res[i] = 0;
	return (res);
}