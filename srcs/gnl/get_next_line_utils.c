/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:17:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 15:14:38 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strclean(char *str)
{
	int	i;
	int	j;
	int	line;

	i = 0;
	j = 0;
	line = 0;
	while (str[i])
	{
		if (line)
			str[j++] = str[i];
		if (str[i] == '\n')
			line = 1;
		str[i++] = '\0';
	}
	return (line);
}

int	heredoc_error(char *str)
{
	write(2, "warning: here-document \
delimited by end-of-file (wanted ", 58);
	write(2, str, ft_strlen(str));
	write(2, "')\n", 3);
	return (1);
}

void	term_change(void)
{
	int				rc;
	struct termios	termios_new;

	rc = tcgetattr(0, &parser()->termios_save);
	if (rc)
	{
		perror("");
		return ;
	}
	termios_new = parser()->termios_save;
	termios_new.c_lflag |= ECHO;
	rc = tcsetattr(0, 0, &termios_new);
	if (rc)
	{
		perror("");
		return ;
	}
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	char	*a;
	int		i;

	i = 0;
	a = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	parser()->hd_free = a;
	if (!a)
		return (NULL);
	while (s1 && s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	free (s1);
	s1 = NULL;
	while (*s2)
	{
		a[i++] = *s2;
		if (*s2++ == '\n')
			break ;
	}
	a[i] = '\0';
	return (a);
}
