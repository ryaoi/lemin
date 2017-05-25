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



static int      tick_visited(t_line *ptr, t_link *link, t_room *origin, t_room *end)
{
	t_link	    *ptr_link;
	t_room	    *dest_room;
	t_line		*ptr_recur;
	t_line		*ptr_name;
    static int  etape = 0;

	ptr_recur = NULL;
	ptr_name = ptr;
	//sleep(2);
	ft_printf("+------------+\n");
	for (ptr_name = ptr; ptr_name != NULL; ptr_name=ptr_name->next)
		ft_printf("elemets are:%s\n", ptr_name->line);
	ft_printf("+------------+\n");
	ptr_name = ptr;
	if (end->visited == 1)
	{
		free_line(&ptr);
		return (etape);
	}
	while (ptr_name != NULL)
	{
		ptr_link = link;
		while (ptr_link != NULL)
		{
			if ((ft_strcmp(ptr_name->line,ptr_link->src) == 0 &&
				check_name_visited(ptr_link->dest, origin) == 0) ||
				(ft_strcmp(ptr_name->line,ptr_link->dest) == 0 &&
				check_name_visited(ptr_link->src, origin) == 0))
			{
				dest_room = give_the_room(ptr_name->line, ptr_link, origin);
				dest_room->visited = 1;
				new_line(&ptr_recur, dest_room->name);
			}
			ptr_link = ptr_link->next;
		}
		ptr_name = ptr_name->next;
	}
	etape++;
	tick_visited(ptr_recur, link, origin, end);
	free_line(&ptr);
	return (etape);
}

int			      shortest_path_num(t_lem *lem)
{
	t_room	        *ptr;
	t_line			*ptr_line;

	ptr = lem->room;
	ptr_line = NULL;
	new_line(&ptr_line, lem->room->name);
	lem->room->visited = 1;
	lem->short_path_num = tick_visited(ptr_line, lem->link, lem->room, lem->end_room);
    ft_printf("shortest path(int) is:%d\n", lem->short_path_num);
	while (ptr != NULL)
	{
		if (ptr->end == 1 && ptr->visited == 1)
			return (1);
		ptr = ptr->next;
	}
	return (lem->short_path_num);
}
