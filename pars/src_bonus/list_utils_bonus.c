/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:16:25 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 16:55:29 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_map_node	*ft_lstlast(t_map_node *head)
{
	while (head != NULL)
	{		
		if (head->next == NULL)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	ft_lstadd_back(t_map_node *head, t_map_node *new)
{
	t_map_node	*last;

	if (head->next == NULL)
	{
		head->next = new;
		return ;
	}
	last = ft_lstlast(head);
	last->next = new;
}

void	free_list(t_map_node *head)
{
	t_map_node	*remove;

	if (head == NULL)
		return ;
	while (head->next != NULL)
	{
		remove = head->next;
		head->next = head->next->next;
		free(remove->str);
		free(remove);
	}
}
