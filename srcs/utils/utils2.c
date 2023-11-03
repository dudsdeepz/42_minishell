/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:58:01 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/03 10:59:50 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **dup_matrix(char **src)
{
	int		p;
	char	**res;

	p = 0;
	while (src[p++] != 0)
		continue ;
	res = malloc(sizeof(char *) * (p + 1));
	p = -1;
	while (src[++p] != 0)
		res[p] = ft_strdup(src[p]);
	res[p++] = 0;
	return (res);
}

char	*ft_subtokens(const char *s, unsigned int start, size_t len)
{
	char	*i;
	size_t	b;

	b = 0;
	if (start >= ft_strlen(s))
	{
		i = (char *)malloc(sizeof(char));
		*i = 0;
		return (i);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	i = (char *)malloc(len + 1);
	if (!i)
		return (0);
	while (start < ft_strlen(s) && b < len)
		i[b++] = s[start++];
	i[b] = '\0';
	return (i);
}

size_t  ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (reject[k] != '\0')
		{
			if (reject[k] == s[i])
				return (i);
			k++;
		}
		k = 0;
		i++;
	}
	return (i);
}

void free_heredoc(char *heredoc_content)
{
	if (heredoc_content != NULL)
		free(heredoc_content);
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
