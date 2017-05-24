/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usefull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:02:50 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/18 17:06:34 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_one_line(char *str)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			total++;
		i++;
	}
	if (total == 1)
		return (1);
	return (0);
}

void 		reset_visited(t_lem *lem)
{
	t_room	*ptr;

	ptr = lem->room;
	while (ptr != NULL)
	{
		ptr->visited = 0;
		ptr = ptr->next;
	}
}
