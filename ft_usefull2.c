/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usefull2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 16:11:27 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 03:39:11 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			total_path(t_path *path)
{
	t_path	*ptr;
	int		ret;

	ret = 0;
	ptr = path;
	while (ptr != NULL)
	{
		ret++;
		ptr = ptr->next;
	}
	return (ret);
}

void		free_path(t_path **origin)
{
	t_line	*ptr;
	t_path	*ptr_path;
	t_path	*ptr_path_next;
	t_line	*ptr_next;

	ptr_path = *origin;
	while (ptr_path != NULL)
	{
		ptr_path_next = ptr_path->next;
		ptr = ptr_path->line;
		while (ptr != NULL)
		{
			ptr_next = ptr->next;
			free(ptr->line);
			free(ptr);
			ptr = ptr_next;
		}
		free(ptr_path);
		ptr_path = ptr_path_next;
	}
}

void		sort_path(t_path **origin, t_lem *lem)
{
	t_path	*ptr1;
	int		stock;
	int		total;
	int		counter;

	total = total_path(*origin);
	lem->total_path = total;
	stock = lem->short_path_num;
	counter = 0;
	while (total > counter)
	{
		ptr1 = *origin;
		while (ptr1 != NULL)
		{
			if (ptr1->step == stock)
			{
				ptr1->order = counter + 1;
				counter++;
			}
			ptr1 = ptr1->next;
		}
		stock++;
	}
}

static void	add_ants(t_path **path, t_lem *lem)
{
	t_line	*ptr;

	ptr = (*path)->line->next;
	if (lem->left_ants != 0 && (*path)->step <
		lem->left_ants + lem->short_path_num)
	{
		ptr->ants = lem->ants - lem->left_ants + 1;
		(lem->left_ants)--;
	}
	else
		ptr->ants = 0;
}

void		move_left(t_path **path, t_lem *lem)
{
	t_line	*ptr;
	int		stock;
	int		tmp;

	ptr = (*path)->line->next;
	stock = ptr->ants;
	if (ptr == (*path)->ptr_end)
	{
		(*path)->ptr_end->ants = stock;
		add_ants(path, lem);
		return ;
	}
	ptr = ptr->next;
	while (ptr->next != NULL)
	{
		tmp = ptr->ants;
		ptr->ants = stock;
		stock = tmp;
		ptr = ptr->next;
	}
	ptr->ants = stock;
	add_ants(path, lem);
}
