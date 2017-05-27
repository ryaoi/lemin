/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:00:19 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 03:25:06 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		new_room(t_room **begin, char *line, int start, int end)
{
	t_room	*new;
	char	**tab;

	tab = ft_strsplit(line, ' ');
	if (!(new = malloc(sizeof(t_room))))
		exit(EXIT_FAILURE);
	new->name = ft_strdup(tab[0]);
	if (tab[1] != 0 && ft_str_isdigit(tab[1]) == 1 && ft_atoi(tab[1]) >= 0)
		new->x = ft_atoi(tab[1]);
	else
		msg_error();
	if (tab[2] != 0 && ft_str_isdigit(tab[2]) == 1 && ft_atoi(tab[2]) >= 0)
		new->y = ft_atoi(tab[2]);
	else
		msg_error();
	new->start = start;
	new->end = end;
	new->visited = 0;
	new->ant = 0;
	new->next = NULL;
	connecting_room(&new, begin);
	ft_str2del(&tab);
}

void		free_room(t_room **begin)
{
	t_room	*ptr;
	t_room	*next;

	ptr = *begin;
	while (ptr != NULL)
	{
		next = ptr->next;
		free(ptr->name);
		free(ptr);
		ptr = next;
	}
}

int			exist_room(t_room *origin, char *name)
{
	t_room	*ptr;
	char	**tab;
	int		check_xy;

	tab = ft_strsplit(name, ' ');
	check_xy = 0;
	if (ft_strchr(tab[0], '-') == NULL)
	{
		if (tab[1] == 0)
			msg_error();
		if (tab[2] == 0)
			msg_error();
		check_xy = 1;
	}
	ptr = origin;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->name, tab[0]) == 0 ||
			((check_xy == 1) && ft_atoi(tab[1]) == ptr->x
			&& ft_atoi(tab[2]) == ptr->y))
			return (1);
		ptr = ptr->next;
	}
	ft_str2del(&tab);
	return (0);
}

int			check_room(char *str1, char *str2, t_room *list)
{
	int		check1;
	int		check2;
	t_room	*ptr;

	check1 = 0;
	check2 = 0;
	ptr = list;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->name, str1) == 0)
			check1++;
		if (ft_strcmp(ptr->name, str2) == 0)
			check2++;
		ptr = ptr->next;
	}
	return ((check1 == 1 && check2 == 1));
}

void		assign_start_end_room(t_lem *lem)
{
	t_room	*ptr;

	ptr = lem->room;
	while (ptr != NULL)
	{
		if (ptr->start == 1)
			lem->start_room = ptr;
		if (ptr->end == 1)
			lem->end_room = ptr;
		ptr = ptr->next;
	}
}
