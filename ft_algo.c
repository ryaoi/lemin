/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:05:05 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/24 13:05:08 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//not left right
//need to find the shortest path in int
//then search if any other path has the same number of path
//if both start defieerently and end differently then its good



static int      tick_visited(t_room **ptr, t_link *link, t_room *origin, t_room *end)
{
	t_link	    *ptr_link;
	t_room	    *dest_room;
    static int  ret = 0;

	ptr_link = link;
    (*ptr)->visited = 1;
	if (end->visited == 1)
		return (ret);
	while (ptr_link != NULL)
	{
		if (ft_strcmp((*ptr)->name,ptr_link->src) == 0 ||
			ft_strcmp((*ptr)->name,ptr_link->dest) == 0)
		{
			dest_room = give_the_room(ptr, ptr_link, origin);
			if (dest_room->visited == 0)
            {
				if (ft_strcmp(ptr_link->dest,origin->name) == 0 ||
					ft_strcmp(ptr_link->src,origin->name) == 0)
					ret = 1;
				else
                	ret++;
				tick_visited(&(dest_room), link, origin, end);
            }
		}
		ptr_link = ptr_link->next;
	}
	if (ret == 0)
		while (1);
	return (ret);
}

int			      shortest_path_num(t_lem *lem)
{
	t_room	        *ptr;
    int             ret;

	ptr = lem->room;
	ret = tick_visited(&(lem->room), lem->link, lem->room, lem->end_room);
    ft_printf("ret is:%d\n", ret);
	while (ptr != NULL)
	{
		if (ptr->end == 1 && ptr->visited == 1)
			return (1);
		ptr = ptr->next;
	}
	return (ret);
}
