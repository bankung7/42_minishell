/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:29:16 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/11 16:42:51 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*n;

	if (*lst)
	{
		while (*lst)
		{
			n = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = n;
		}
	}
	else
		return ((void)0);
}
