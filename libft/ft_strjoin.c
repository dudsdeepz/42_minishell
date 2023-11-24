/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:16:41 by eduardo           #+#    #+#             */
/*   Updated: 2023/11/23 10:49:54 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*a;
	size_t	i;
	size_t	i2;

	a = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	i2 = 0;
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	s1 = NULL;
	while (s2[i2])
	{
		a[i + i2] = s2[i2];
		i2++;
	}
	a[i + i2] = '\0';
	s2 = NULL;
	return (a);
}
