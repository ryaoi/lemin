/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usefull1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:02:50 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 03:34:02 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_one_line(char *str)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			total++;
		i++;
	}
	if (total == 1)
		return (1);
	return (0);
}

void		reset_visited(t_lem *lem)
{
	t_room	*ptr;

	ptr = lem->room;
	while (ptr != NULL)
	{
		ptr->visited = 0;
		ptr = ptr->next;
	}
}

void		init_start(t_lem *lem)
{
	t_room	*ptr;
	char	*tmp;

	ptr = lem->room;
	while (ptr->start != 1)
		ptr = ptr->next;
	if (ptr == lem->room)
		return ;
	lem->room->start = 1;
	ptr->start = 0;
	tmp = ft_strdup(lem->room->name);
	free(lem->room->name);
	lem->room->name = ft_strdup(ptr->name);
	free(ptr->name);
	ptr->name = ft_strdup(tmp);
	ft_strdel(&tmp);
}

t_room		*give_the_room(char *name, t_link *ptr_link, t_room *origin)
{
	t_room	*dest_room;

	dest_room = origin;
	if (ft_strcmp(name, ptr_link->src) == 0)
	{
		while (ft_strcmp(dest_room->name, ptr_link->dest) != 0)
			dest_room = dest_room->next;
	}
	else
	{
		while (ft_strcmp(dest_room->name, ptr_link->src) != 0)
			dest_room = dest_room->next;
	}
	return (dest_room);
}

int			check_name_visited(char *name, t_room *origin)
{
	t_room	*ptr;

	ptr = origin;
	while (ptr != NULL)
	{
		if (ft_strcmp(name, ptr->name) == 0)
		{
			if (ptr->visited == 1)
				return (1);
			else
				return (0);
		}
		ptr = ptr->next;
	}
	return (0);
}
