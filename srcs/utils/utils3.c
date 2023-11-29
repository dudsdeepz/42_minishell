/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:00:42 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/29 10:45:46 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*triple_strjoin(char *s1, char *s2, char *s3)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	while (*s3)
		res[i++] = *s3++;
	res[i] = 0;
	return (res);
}

void	print_tokens(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}
	printf("====\n");
}

void	sig_actions(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	free_envs(void)
{
	free_matrix(parser()->envp);
	free_matrix(parser()->export_env);
}

int	lstsize_tokens(t_tokens *lst)
{
	int			count;
	t_tokens	*ptr;

	count = 0;
	if (!lst)
		return (0);
	ptr = lst;
	while (ptr->next)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
