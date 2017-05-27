/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usefull3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:54:06 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 14:29:41 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		solver_loop(t_lem *lem, t_path *path)
{
	int		counter;
	t_path	*ptr_path;

	while (lem->exited_ants != lem->ants)
	{
		if (lem->opt_v == 1)
			ft_printf("\n[turn:%d]\n", lem->turn);
		counter = 1;
		while (lem->total_path + 1 != counter && lem->exited_ants != lem->ants)
		{
			ptr_path = path;
			while (ptr_path->order != counter)
				ptr_path = ptr_path->next;
			move_left(&ptr_path, lem);
			if (ptr_path->ptr_end->ants != 0)
				(lem->exited_ants)++;
			counter++;
			option_verbose(path, lem);
		}
		print_ants(path, lem);
		(lem->turn)++;
	}
}

void		loop_for_copying(t_line **ptr_old, t_line **ptr, t_line **ptr_next)
{
	while (*ptr_old != NULL)
	{
		if (!((*ptr_next) = malloc(sizeof(t_line))))
			exit(EXIT_FAILURE);
		(*ptr_next)->next = NULL;
		(*ptr_next)->line = ft_strdup((*ptr_old)->line);
		(*ptr)->next = *ptr_next;
		(*ptr_next)->ants = 0;
		*ptr_next = NULL;
		*ptr = (*ptr)->next;
		(*ptr_old) = (*ptr_old)->next;
	}
}
