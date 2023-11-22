/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:17:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 21:31:16 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
	
char	*ft_strjoin(char *s1, char *s2)
{
	char	*a;
	int		i;

	i = 0;
	a = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!a)
		return (NULL);
	while (s1 && s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	free (s1);
	while (*s2)
	{
		a[i++] = *s2;
		if (*s2++ == '\n')
			break ;
	}
	a[i] = '\0';
	return (a);
}

int	ft_strclean(char *str)
{
	int	i;
	int	j;
	int	line;

	i = 0;
	j = 0;
	line = 0;
	while (str[i])
	{
		if (line)
			str[j++] = str[i];
		if (str[i] == '\n')
			line = 1;
		str[i++] = '\0';
	}
	return (line);
}
