/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstpush(t_list **from, t_list **to)
{
	t_list	*node;
	t_list	*next;

	if (from == NULL || to == NULL || from == to || ft_lstsize(*from) == 0)
		return ;
	node = *from;
	next = (*from)->next;
	ft_lstadd_front(to, node);
	*from = next;
}
