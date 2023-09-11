/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:05:12 by eduarodr          #+#    #+#             */
/*   Updated: 2023/09/04 14:58:25 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_putstr(char *str, char *color)
{
	int i = 0;
	int j = 0;

	if (color)
	{
		while (color[i])
		{
			write(1, &color[i], 1);
			i++;
		}
	}
	if (str)
	{
		while (str[j])
		{
			write(1, &str[j], 1);
			j++;
		}
	}
	return (str);
}

t_tokens	*tokens(void)
{
	static t_tokens	tokens;

	return (&tokens);
}

char *ft_strremove(char *substr) 
{
    size_t i;

	i = 0;
	while (substr[i] != 0)
	{
		i++;
		substr[i - 1] = '\0';
	}
	substr[i] -= 1;
    return (substr);
}