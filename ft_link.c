/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:00:19 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 03:24:11 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		new_link(t_link **begin, char *src, char *dest)
{
	t_link	*new;
	t_link	*ptr;

	if (!(new = malloc(sizeof(t_link))))
		exit(EXIT_FAILURE);
	new->src = ft_strdup(src);
	new->dest = ft_strdup(dest);
	new->next = NULL;
	new->prev = NULL;
	if (*begin == NULL)
		*begin = new;
	else
	{
		ptr = *begin;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
}

void		free_link(t_link **begin)
{
	t_link	*ptr;
	t_link	*next;

	ptr = *begin;
	while (ptr != NULL)
	{
		next = ptr->next;
		free(ptr->src);
		free(ptr->dest);
		free(ptr);
		ptr = next;
	}
}

int			check_exist_link(char *str1, char *str2, t_link *link)
{
	t_link	*ptr;

	ptr = link;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->src, str1) == 0 &&
			ft_strcmp(ptr->dest, str2) == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static void	tick_visited(t_room **ptr, t_link *link,
						t_room *origin, t_room *end)
{
	t_link	*ptr_link;
	t_room	*dest_room;

	ptr_link = link;
	if (end->visited == 1)
		return ;
	(*ptr)->visited = 1;
	while (ptr_link != NULL)
	{
		if (ft_strcmp((*ptr)->name, ptr_link->src) == 0 ||
			ft_strcmp((*ptr)->name, ptr_link->dest) == 0)
		{
			dest_room = give_the_room((*ptr)->name, ptr_link, origin);
			if (dest_room->visited == 0)
				tick_visited(&(dest_room), link, origin, end);
		}
		ptr_link = ptr_link->next;
	}
}

int			check_link_start_end(t_lem *lem)
{
	t_room	*ptr;

	init_start(lem);
	ptr = lem->room;
	tick_visited(&(lem->room), lem->link, lem->room, lem->end_room);
	while (ptr != NULL)
	{
		if (ptr->end == 1 && ptr->visited == 1)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
