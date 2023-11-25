/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:17:37 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/25 20:19:55 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	saved[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	line = 0;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		while (saved[i])
			saved[i++] = 0;
		return (NULL);
	}
	while (saved[0] || read(fd, saved, BUFFER_SIZE) > 0)
	{
		line = ft_strjoingnl(line, saved);
		if (ft_strclean(saved))
			break ;
	}
	return (line);
}
