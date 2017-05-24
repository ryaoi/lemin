/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:05:17 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/24 13:05:19 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void     not_valid_input(t_lem *lem)
{
    if (check_start_end(lem->room) == 1)
        ft_printf("Start and end are not linked.\n");
        //ft_printf("Error\n");
    else if (check_start_end(lem->room) == 2)
        ft_printf("Only one start and one end.\n");
        //ft_printf("Error\n");
    else
        ft_printf("Missing start, end or both.\n");
        //ft_printf("Error\n");
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
        ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
}
