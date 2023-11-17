/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:20:41 by eduardo           #+#    #+#             */
/*   Updated: 2023/11/15 18:09:20 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*i;
	size_t	b;

	b = 0;
	if (start > len)
		return (NULL);
	if ((size_t)len > ft_strlen(s))
		len = ft_strlen(s) - start;
	i = (char *)malloc(len + 1);
	if (!i)
		return (0);
	while (start <= len)
	{
		i[b] = s[start];
		start++;
		b++;
	}
	i[b] = '\0';
	return (i);
}
