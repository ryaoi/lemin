/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:13:20 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 03:32:29 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				valid_parse_room(t_lem *lem, char *line, int *room_def)
{
	char		**tab;

	if (line[0] != '-' && line[ft_strlen(line) - 1] != '-'
		&& check_one_line(line) == 1)
	{
		tab = ft_strsplit(line, '-');
		if (check_room(tab[0], tab[1], lem->room) == 1 &&
			check_exist_link(tab[0], tab[1], lem->link) == 0)
			new_link(&(lem->link), tab[0], tab[1]);
		else if (check_room(tab[0], tab[1], lem->room) == 1 &&
			check_exist_link(tab[0], tab[1], lem->link) == 1)
			msg_error();
		else
			msg_error();
		ft_str2del(&tab);
		*room_def = 1;
		return (1);
	}
	return (0);
}

int				check_start_end(t_room *begin)
{
	t_room		*ptr;
	int			start;
	int			end;

	start = 0;
	end = 0;
	ptr = begin;
	while (ptr != NULL)
	{
		if (ptr->start == 1)
			start++;
		if (ptr->end == 1)
			end++;
		ptr = ptr->next;
	}
	if ((start == 1 && end == 1))
		return (1);
	if (start > 1 || end > 1)
		return (2);
	return (0);
}
