/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:20:41 by eduardo           #+#    #+#             */
/*   Updated: 2022/11/10 18:06:17 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
