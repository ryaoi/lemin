/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:00:07 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/22 16:34:10 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include "libft/libft.h"

typedef struct		s_room
{
	char			*name;
	int				start;
	int				end;
	int				visited;
	int				ant;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	char			*src;
	char			*dest;
	struct s_link	*next;
}					t_link;

typedef	struct		s_lem
{
	int				ants;
	t_room			*room;
	t_link			*link;
	t_room			*start_room;
	t_room			*end_room;
	int				room_nb;
}					t_lem;

void				new_room(t_room **begin, char *line, int start, int end);
void				free_room(t_room **begin);
void				new_link(t_link **begin, char *src, char *dest);
void				free_link(t_link **begin);
int					check_room(char *str1, char *str2, t_room *list);
int					check_one_line(char *str);
int					valid_parse_room(t_lem *lem, char *line, int *room_def);
int					check_start_end(t_room *begin);
int					check_exist_link(char *str1, char *str2, t_link *link);
int					check_link_start_end(t_lem *lem);
void 				assign_start_end_room(t_lem *lem);

#endif
