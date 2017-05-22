/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:13:20 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/18 19:19:43 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			valid_parse_room(t_lem *lem, char *line, int *room_def)
{
	char	**tab;
	int		i;

	if (line[0] != '-' && line[ft_strlen(line) - 1] != '-'
		&& check_one_line(line) == 1)
	{
		tab = ft_strsplit(line, '-');
		if (check_room(tab[0], tab[1], lem->room) == 1 &&
			check_exist_link(tab[0], tab[1], lem->link) == 0)
			new_link(&(lem->link), tab[0], tab[1]);
		else if (check_room(tab[0], tab[1], lem->room) == 1 &&
			check_exist_link(tab[0], tab[1], lem->link) == 1)
			ft_printf("Already exist...");
		else
			ft_printf("Invalid name\n");
		i = 0;
		while (tab[i] != 0)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
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
	return ((start == 1 && end == 1));
}
