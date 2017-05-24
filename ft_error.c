#include "lemin.h"

void     not_valid_input(t_lem *lem)
{
    if (check_start_end(lem->room) == 1)
        ft_printf("Start and end are not linked.\n");
    else if (check_start_end(lem->room) == 2)
        ft_printf("Only one start and one end.\n");
    else
        ft_printf("Missing start, end or both.\n");
    free_room(&(lem->room));
    free_link(&(lem->link));
    exit(EXIT_FAILURE);
}

void    check_ants(t_lem *lem, char *line)
{
    if (line != NULL && line[0] != '-')
		lem->ants = ft_atoi(line);
	if (lem->ants <= 0 || line == NULL)
	{
        ft_strdel(&line);
		ft_printf("Without ants, this program won't execute.\n");
		exit(EXIT_FAILURE);
	}
}
