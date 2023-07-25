/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:56:15 by eduardo           #+#    #+#             */
/*   Updated: 2022/10/31 15:49:56 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	c;
	size_t	d;

	a = ft_strlen(dst);
	c = ft_strlen(src);
	d = a;
	b = 0;
	if (size == 0 || size <= d)
		return (size + c);
	while (src[b] && (b < (size - a - 1)))
		dst[d++] = src[b++];
	dst[d] = '\0';
	return (a + c);
}
