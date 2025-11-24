/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_coll_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:48:59 by sabadri          #+#    #+#             */
/*   Updated: 2025/11/21 22:00:59 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	garb_del_node(t_garbage *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	free(node);
}

//Free the garbage_collector list.
void	garbage_clear(t_garbage **garb_list)
{
	t_garbage	*current;
	t_garbage	*tmp;

	if (!garb_list || !*garb_list)
		return ;
	current = *garb_list;
	while (current)
	{
		tmp = current;
		current = current->next;
		garb_del_node(tmp);
	}
	*garb_list = NULL;
}
