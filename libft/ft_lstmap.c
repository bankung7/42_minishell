/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:48:04 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/11 17:17:39 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*h;
	t_list	*n;

	if (!lst)
		return (0);
	h = 0;
	while (lst)
	{
		n = ft_lstnew((*f)(lst->content));
		if (!n)
		{
			ft_lstclear(&h, (*del));
			return (0);
		}
		ft_lstadd_back(&h, n);
		lst = lst->next;
	}
	return (h);
}
