/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:05:05 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 03:20:50 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		init_and_end(t_line **ptr_recur, t_line *ptr, t_room *end,
							t_line **ptr_name)
{
	(*ptr_recur) = NULL;
	(*ptr_name) = ptr;
	if (end->visited == 1)
	{
		free_line(&ptr);
		return (1);
	}
	return (0);
}

static int		valid_link(t_tick tick, t_room *origin)
{
	if ((ft_strcmp(tick.ptr_name->line, tick.ptr_link->src) == 0 &&
		check_name_visited(tick.ptr_link->dest, origin) == 0) ||
		(ft_strcmp(tick.ptr_name->line, tick.ptr_link->dest) == 0 &&
		check_name_visited(tick.ptr_link->src, origin) == 0))
		return (1);
	return (0);
}

static int		tick_visited(t_line *ptr, t_link *link, t_room *origin,
							t_room *end)
{
	t_tick		tick;
	static int	etape = 0;

	if (init_and_end(&(tick.ptr_recur), ptr, end, &(tick.ptr_name)) == 1)
		return (etape);
	while ((tick.ptr_name) != NULL)
	{
		tick.ptr_link = link;
		while ((tick.ptr_link) != NULL)
		{
			if (valid_link(tick, origin) == 1)
			{
				tick.dest_room = give_the_room(tick.ptr_name->line,
												tick.ptr_link, origin);
				tick.dest_room->visited = 1;
				new_line(&(tick.ptr_recur), tick.dest_room->name);
			}
			tick.ptr_link = tick.ptr_link->next;
		}
		tick.ptr_name = tick.ptr_name->next;
	}
	etape++;
	tick_visited(tick.ptr_recur, link, origin, end);
	free_line(&ptr);
	return (etape);
}

int				shortest_path_num(t_lem *lem)
{
	t_room		*ptr;
	t_line		*ptr_line;

	ptr = lem->room;
	ptr_line = NULL;
	new_line(&ptr_line, lem->room->name);
	lem->room->visited = 1;
	lem->short_path_num = tick_visited(ptr_line, lem->link, lem->room,
										lem->end_room);
	while (ptr != NULL)
	{
		if (ptr->end == 1 && ptr->visited == 1)
			return (1);
		ptr = ptr->next;
	}
	return (lem->short_path_num);
}
