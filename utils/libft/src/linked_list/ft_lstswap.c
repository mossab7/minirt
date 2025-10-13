/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstswap(t_list **head)
{
	void	*tmp;
	t_list	*node;
	t_list	*next;

	if (ft_lstsize(*head) <= 1)
		return ;
	node = *head;
	next = (*head)->next;
	tmp = node->content;
	node->content = next->content;
	next->content = tmp;
}
