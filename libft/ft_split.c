/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:18:09 by eduardo           #+#    #+#             */
/*   Updated: 2022/11/08 17:41:11 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**recursive(char **split, int count, char c, char const *s)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (s && *s && *s == c)
		s++;
	while (*s && s[i] && s[i] != c)
		i++;
	if (i > 0)
		str = malloc(sizeof(char) * i + 1);
	if (str)
		str[i] = '\0';
	i = 0;
	while (str && s && *s && *s != c)
		str[i++] = *s++;
	if (str)
		split = recursive(split, count + 1, c, s);
	else
		split = malloc(sizeof(char *) * (count + 1));
	if (split)
		split[count] = str;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	return (recursive(NULL, 0, c, s));
}
