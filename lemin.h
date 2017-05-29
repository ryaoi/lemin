/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:00:07 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 14:29:02 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"

typedef struct		s_room
{
	char			*name;
	int				start;
	int				end;
	int				x;
	int				y;
	int				visited;
	int				ant;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	char			*src;
	char			*dest;
	struct s_link	*next;
	struct s_link	*prev;
}					t_link;

typedef struct		s_line
{
	char			*line;
	int				ants;
	struct s_line	*next;
}					t_line;

typedef struct		s_tick
{
	t_link		*ptr_link;
	t_room		*dest_room;
	t_line		*ptr_recur;
	t_line		*ptr_name;
}					t_tick;

typedef struct		s_path
{
	t_line			*line;
	struct s_path	*next;
	int				end;
	int				step;
	int				order;
	t_line			*ptr_end;
}					t_path;

typedef	struct		s_lem
{
	int				ants;
	int				exited_ants;
	int				left_ants;
	int				short_path_num;
	int				total_path;
	int				turn;
	int				opt_v;
	t_room			*room;
	t_link			*link;
	t_line			*sentence;
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
void				assign_start_end_room(t_lem *lem);
void				not_valid_input(t_lem *lem);
void				check_ants(t_lem *lem, char *line);
void				reset_visited(t_lem *lem);
int					exist_room(t_room *origin, char *name);
void				shortest_path_num(t_lem *lem);
void				init_start(t_lem *lem);
t_room				*give_the_room(char *name,
					t_link *ptr_link, t_room *origin);
void				new_line(t_line **begin, char *line);
void				free_line(t_line **begin);
void				print_all_line(t_line *sentence);
int					check_name_visited(char *name, t_room *origin);
void				new_path(t_path **begin, char *start);
void				copy_add_path(t_path **begin, t_path *old, char *room);
void				free_path(t_path **origin);
void				solver(t_lem *lem);
void				copy_path(t_path **begin, t_path *old);
int					total_path(t_path *path);
void				sort_path(t_path **origin, t_lem *lem);
void				move_left(t_path **path, t_lem *lem);
void				print_ants(t_path *path, t_lem *lem);
void				msg_error(void);
int					ft_str_isdigit(char *line);
void				connecting_room(t_room **new, t_room **begin);
void				option_verbose(t_path *path, t_lem *lem);
void				solver_loop(t_lem *lem, t_path *path);
void				loop_for_copying(t_line **ptr_old,
					t_line **ptr, t_line **ptr_next);

#endif
