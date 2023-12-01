/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:58:01 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 15:18:23 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**dup_matrix(char **src)
{
	int		p;
	char	**res;

	p = 0;
	while (src[p++] != 0)
		continue ;
	res = malloc(sizeof(char *) * (p + 1));
	p = -1;
	while (src[++p] != 0)
		res[p] = ft_strdup(src[p]);
	res[p] = 0;
	return (res);
}

char	*ft_subtokens(const char *s, unsigned int start, size_t len)
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

void	go_top(t_tokens **lst)
{
	while ((lst) && (*lst) && (*lst)->next)
		(*lst) = (*lst)->next;
}

void	handle_signals2(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, 0);
	if (pid == -1)
		SIG_IGN ;
	else if (!parser()->hd)
	{
		parser()->exit_status = 131;
		write(1, "Quit\n", 5);
		return ;
	}
}

void	get_stts_utils(char *str, int i, char *val, char **res)
{
	int		k;
	int		j;
	int		l;

	l = 0;
	k = 0;
	j = 0;
	while (str[k + l])
	{
		if ((k + j) == i)
		{
			while (val[j])
			{
				(*res)[k + j] = val[j];
				j++;
			}
			l = 2;
		}
		else
		{
			(*res)[k + j] = str[k + l];
			k++;
		}
	}
	(*res)[k + j] = 0;
}
