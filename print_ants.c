/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 03:51:41 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/28 14:33:59 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	count_all_ants(t_path *path, int *smallest)
{
	int		total;
	t_line	*ptr_line;
	t_path	*ptr;

	ptr = path;
	total = 0;
	while (ptr != NULL)
	{
		ptr_line = ptr->line->next;
		while (ptr_line != NULL)
		{
			if (*smallest > ptr_line->ants && ptr_line->ants != 0)
				*smallest = ptr_line->ants;
			if (ptr_line->ants != 0)
				total++;
			ptr_line = ptr_line->next;
		}
		ptr = ptr->next;
	}
	return (total);
}

static void	search_and_print(t_path *path, int size, int *i, int total)
{
	t_line	*ptr_line;
	t_path	*ptr;

	ptr = path;
	while (ptr != NULL)
	{
		ptr_line = ptr->line->next;
		while (ptr_line != NULL)
		{
			if (size == ptr_line->ants)
			{
				ft_printf("L%d-%s", ptr_line->ants, ptr_line->line);
				if (*i < total - 1)
					ft_putstr(" ");
				else
					ft_putstr("\n");
				(*i)++;
			}
			ptr_line = ptr_line->next;
		}
		ptr = ptr->next;
	}
}

void		print_ants(t_path *path, t_lem *lem)
{
	int		smallest;
	int		total;
	int		i;

	smallest = lem->ants;
	total = count_all_ants(path, &smallest);
	i = 0;
	while (smallest <= lem->ants)
	{
		search_and_print(path, smallest, &i, total);
		smallest++;
	}
}

static void	printing_for_verbose(t_path *w, t_line *e, t_lem *lem)
{
	int		i;

	if (e == w->line)
	{
		ft_printf("%s(", e->line);
		i = lem->ants - lem->left_ants + 1;
		while (i < lem->ants + 1)
		{
			ft_printf("%d", i);
			if (i < lem->ants)
				ft_printf(",");
			i++;
		}
		ft_printf(")---");
	}
	else if (e->next != NULL)
		ft_printf("%s(%d)---", e->line, e->ants);
	else
		ft_printf("%s(%d)", e->line, w->ptr_end->ants);
}

void		option_verbose(t_path *path, t_lem *lem)
{
	t_path	*w;
	t_line	*e;

	if (lem->opt_v == 0)
		return ;
	w = path;
	ft_printf("------------------------------\n");
	while (w != NULL)
	{
		e = w->line;
		ft_printf("order:%d\tstep:%d\t", w->order, w->step);
		while (e != NULL)
		{
			printing_for_verbose(w, e, lem);
			e = e->next;
		}
		ft_printf("\n");
		w = w->next;
	}
	ft_printf("------------------------------\n");
}
