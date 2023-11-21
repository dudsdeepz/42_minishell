/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:00:42 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/21 15:42:02 by eduarodr         ###   ########.fr       */
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
	int i;
	
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
	int		count;
	t_tokens	*ptr;

	count = 0;
	if (!lst)
		return (0);
	ptr = lst;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count - 1);
}


t_tokens	*lstlast_tokens(t_tokens *lst)
{
	t_tokens	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

int	total_tokens_size(t_tokens **tokens)
{
	int count;

	count = 0;
	go_head(tokens);
	while ((*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		count++;
	}
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
			i++;
		return (s1[i] - s2[i]);
	}
	return (1);
}


t_tokens	*ft_lstlasttoken(t_tokens *lst)
{
	t_tokens	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_token(t_tokens **lst, t_tokens *new)
{
	if (!lst || !new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			new->prev = ft_lstlasttoken(*lst);
			ft_lstlasttoken(*lst)->next = new;
		}
		else
			*lst = new;

	}
}

t_tokens	*ft_lstnewtoken(int token_size)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token = malloc(sizeof(char *) * token_size);
	pipe(new->fd);
	new->fd_master[0] = 0;
	new->fd_master[1] = 1;
	return (new);
}


void	go_head(t_tokens **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}

