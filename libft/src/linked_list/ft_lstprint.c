/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:22:37 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/24 17:22:50 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

void    ft_lstprint(t_list *lst, void (*print_content)(void *))
{
	printf("------\n");
    while (lst)
    {
        print_content(lst->content);
        lst = lst->next;
    }
	printf("------\n");
}
