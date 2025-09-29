/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse_rotate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstreverse_rotate(t_list **head)
{
	t_list	*last;
	t_list	**list;

	if (head == NULL || ft_lstsize(*head) <= 1)
		return ;
	last = ft_lstlast(*head);
	last->next = *head;
	list = head;
	while ((*list)->next != last)
		*list = (*list)->next;
	(*list)->next = NULL;
	*head = last;
}
