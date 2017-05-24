/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:02:40 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/22 16:46:38 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			get_room_tube(t_lem *lem, char *line)
{
	int			room_def;
	int			start;
	int			end;

	start = 0;
	end = 0;
	room_def = 0;
	while (1)
	{
		get_next_line(0, &line);
		if (line == NULL || ft_strlen(line) == 0)
			break ;
		if (line != NULL)
		{
			if (ft_strcmp(line, "##start") == 0)
				start = 1;
			else if (ft_strcmp(line, "##end") == 0)
				end = 1;
			else if (line[0] =='#');
			else if (ft_strchr(line, '-') == NULL && room_def == 0
					&& exist_room(lem->room, line) == 0);
			{
				new_room(&(lem->room), line, start, end);
				start = 0;
				end = 0;
			}
			else if (ft_strchr(line, '-') == NULL && room_def == 1)
				ft_printf("You can not define a room anymore\n");
			else if (valid_parse_room(lem, line, &room_def) == 0)
				ft_printf("Invalid syntax\n");
			ft_strdel(&line);
		}
	}
}

int				main(void)
{
	t_lem		lem;
	char		*line;

	line = NULL;
	lem.room_nb = 0;
	lem.link = NULL;
	get_next_line(0, &line);
	check_ants(&lem, line);
	ft_strdel(&line);
	get_room_tube(&lem, line);

	//printing tool
	t_room	*ptr;
	for (ptr = lem.room;ptr != NULL;ptr = ptr->next)
		ft_printf("room:%-10s\tstart:%d\tend:%d\tvisited:%d\n", ptr->name, ptr->start, ptr->end, ptr->visited);
	t_link *ptr_link;
	for (ptr_link = lem.link;ptr_link != NULL;ptr_link = ptr_link->next)
		ft_printf("src:%10s --- dest:%-10s\n", ptr_link->src, ptr_link->dest);
	//end printing tool

	assign_start_end_room(&lem);
	if (check_start_end(lem.room) == 1 && check_link_start_end(&lem) == 1)
	{
		//debug tool
		for (ptr = lem.room;ptr != NULL;ptr = ptr->next)
			ft_printf("room:%-10s\tstart:%d\tend:%d\tvisited:%d\n", ptr->name, ptr->start, ptr->end, ptr->visited);
		//debug end

		ft_printf("good\n");
		reset_visited(&lem);
	}
	else
		not_valid_input(&lem);
	if (line != NULL)
		ft_strdel(&line);
	free_room(&(lem.room));
	free_link(&(lem.link));
	return (0);
}
