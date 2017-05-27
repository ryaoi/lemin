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

void     msg_error(void)
{
    ft_printf("Error\n");
    exit(EXIT_FAILURE);
}

void     not_valid_input(t_lem *lem)
{
    if (check_start_end(lem->room) == 1)
        ft_printf("Error\n");
    else if (check_start_end(lem->room) == 2)
        ft_printf("Error\n");
    else
        ft_printf("Error\n");
    free_room(&(lem->room));
    free_link(&(lem->link));
    exit(EXIT_FAILURE);
}

int         ft_str_isdigit(char *line)
{
    int     i;

    i = 0;
    while (line[i] != '\0')
    {
        if (ft_isdigit(line[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

void    check_ants(t_lem *lem, char *line)
{
    if (line != NULL && line[0] != '-' && ft_str_isdigit(line) == 1)
		lem->ants = ft_atoi(line);
	if (lem->ants <= 0 || line == NULL || ft_str_isdigit(line) == 0
        || lem->ants > 50000)
	{
        ft_strdel(&line);
        ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
}
