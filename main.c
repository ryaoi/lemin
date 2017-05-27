/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:02:40 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 13:48:38 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		parsing_line(t_lem *lem, char *line)
{
	static int	room_def = 0;
	static int	start = 0;
	static int	end = 0;

	if (ft_strcmp(line, "##start") == 0)
		start = 1;
	else if (ft_strcmp(line, "##end") == 0)
		end = 1;
	else if (line[0] == '#')
		return ;
	else if (ft_strchr(line, '-') == NULL && room_def == 0
			&& exist_room(lem->room, line) == 0 && line[0] != 'L')
	{
		new_room(&(lem->room), line, start, end);
		start = 0;
		end = 0;
	}
	else if (exist_room(lem->room, line) == 1 && room_def == 0)
		msg_error();
	else if (ft_strchr(line, '-') == NULL && room_def == 1)
		msg_error();
	else if (valid_parse_room(lem, line, &room_def) == 0)
		msg_error();
}

static void		get_room_tube(t_lem *lem, char *line)
{
	while (1)
	{
		get_next_line(0, &line);
		if (line == NULL || ft_strlen(line) == 0)
			break ;
		if (line != NULL)
		{
			new_line(&(lem->sentence), line);
			parsing_line(lem, line);
			ft_strdel(&line);
		}
	}
	if (line != NULL)
		ft_strdel(&line);
}

static void		get_ants_number(t_lem *lem, char *line)
{
	get_next_line(0, &line);
	while (line != NULL && line[0] == '#')
	{
		new_line(&(lem->sentence), line);
		ft_strdel(&line);
		get_next_line(0, &line);
	}
	if (line == NULL)
		msg_error();
	new_line(&(lem->sentence), line);
	check_ants(lem, line);
	ft_strdel(&line);
}

static void		processing_checker(t_lem *lem)
{
	if (check_start_end(lem->room) == 1 && check_link_start_end(lem) == 1)
	{
		print_all_line(lem->sentence);
		reset_visited(lem);
		shortest_path_num(lem);
		reset_visited(lem);
		ft_printf("\n");
		solver(lem);
	}
	else
		not_valid_input(lem);
}

int				main(int argc, char **argv)
{
	t_lem		lem;
	char		*line;

	line = NULL;
	lem.room_nb = 0;
	lem.opt_v = 0;
	lem.sentence = NULL;
	lem.link = NULL;
	lem.room = NULL;
	if (argc == 2 && ft_strcmp(argv[1], "-v") == 0)
		lem.opt_v = 1;
	get_ants_number(&lem, line);
	get_room_tube(&lem, line);
	if (lem.link == NULL || lem.room == NULL)
		msg_error();
	assign_start_end_room(&lem);
	processing_checker(&lem);
	if (line != NULL)
		ft_strdel(&line);
	free_line(&(lem.sentence));
	free_room(&(lem.room));
	free_link(&(lem.link));
	return (0);
}
