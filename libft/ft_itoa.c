/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:51:04 by eduarodr          #+#    #+#             */
/*   Updated: 2022/11/02 14:09:59 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	signdef(int n)
{
	if (n > 0)
		return (1);
	return (-1);
}

static int	lendef(int n)
{
	if (n > 0)
		return (0);
	return (1);
}

char	*ft_itoa(int n)
{
	char	*r;
	size_t	len;
	long	num;

	len = lendef(n);
	num = (long)n * signdef(n);
	while (n)
	{
		n /= 10;
		len++;
	}
	r = (char *)malloc(len + 1);
	if (!r)
		return (NULL);
	*(r + len--) = '\0';
	while (num > 0)
	{
		*(r + len--) = num % 10 + 48;
		num /= 10;
	}
	if (len == 0 && r[1] == '\0')
		*(r + len--) = 48;
	else if (len == 0 && r[1] != '\0')
		*(r + len--) = '-';
	return (r);
}
