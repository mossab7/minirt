/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstassign_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:20:10 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/26 17:20:16 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void    ft_lstassign_index(t_list *lst)
{
    int i = 0;
    while (lst)
    {
        lst->index = i++;
        lst = lst->next;
    }
}
