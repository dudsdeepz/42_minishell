/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:36:51 by eduarodr          #+#    #+#             */
/*   Updated: 2022/11/10 17:20:48 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*n;

	n = NULL;
	ptr = *lst;
	while (ptr)
	{
		n = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = n;
	}
	*lst = NULL;
}
