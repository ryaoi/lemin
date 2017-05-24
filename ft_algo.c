#include "lemin.h"

//not left right
//need to find the shortest path in int
//then search if any other path has the same number of path
//if both start defieerently and end differently then its good
char    *left_search_path(t_room **ptr, t_link *link, t_room *origin, t_room *end)
{
    t_link	*ptr_link;
	t_room	*dest_room;
    static char tab[1024];

	ptr_link = link;
	if (end->visited == 1)
		return ;
	(*ptr)->visited = 1;

	while (ptr_link != NULL)
	{
		if (ft_strcmp((*ptr)->name,ptr_link->src) == 0)
		{
			dest_room = origin;
			while (ft_strcmp(dest_room->name, ptr_link->dest) != 0)
				dest_room = dest_room->next;
			if (dest_room->visited == 0)
				tick_visited(&(dest_room), link, origin, end);
		}
		ptr_link = ptr_link->next;
	}
}
