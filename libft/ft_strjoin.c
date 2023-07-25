/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:16:41 by eduardo           #+#    #+#             */
/*   Updated: 2022/10/31 14:07:44 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	i;
	size_t	i2;
	size_t	ss1;
	size_t	ss2;

	ss1 = ft_strlen(s1);
	ss2 = ft_strlen(s2);
	a = (char *)malloc(ss1 + ss2 + 1);
	if (!a)
		return (NULL);
	i = 0;
	i2 = 0;
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	while (s2[i2])
	{
		a[i + i2] = s2[i2];
		i2++;
	}
	a[i + i2] = '\0';
	return (a);
}
