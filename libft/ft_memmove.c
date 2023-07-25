/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:16:59 by eduardo           #+#    #+#             */
/*   Updated: 2022/11/02 12:55:58 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*a;
	char	*b;

	b = dst;
	a = (char *)src;
	if (a < b)
	{
		while (n--)
			b[n] = a[n];
	}
	else
		ft_memcpy(b, a, n);
	return (dst);
}
