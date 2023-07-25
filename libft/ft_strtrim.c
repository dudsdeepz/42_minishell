/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:52:32 by eduardo           #+#    #+#             */
/*   Updated: 2022/11/10 15:12:46 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char s, char const *a)
{
	size_t	i;

	i = 0;
	while (a[i])
	{
		if (a[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	last;
	size_t	first;
	char	*s2;

	first = 0;
	last = ft_strlen(s1);
	while (s1[first] && isset(s1[first], set))
		first++;
	while (last > first && isset(s1[last - 1], set))
		last--;
	s2 = (char *)malloc(sizeof(char) * (last - first + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (first < last)
		s2[i++] = s1[first++];
	s2[i] = 0;
	return (s2);
}
