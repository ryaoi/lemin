/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:53:50 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/25 15:53:51 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char		*valid_link(char *cmp, t_link *ptr_link, t_room **origin,
                            t_lem *lem)
{
	if ((ft_strcmp(cmp, ptr_link->src) == 0 &&
		check_name_visited(ptr_link->dest, *origin) == 0)
        || (ft_strcmp(cmp, ptr_link->src) == 0 &&
            ft_strcmp(lem->end_room->name, ptr_link->dest) == 0))
        return (ptr_link->dest);
	if ((ft_strcmp(cmp, ptr_link->dest) == 0 &&
		check_name_visited(ptr_link->src, *origin) == 0)
        || (ft_strcmp(cmp, ptr_link->dest) == 0 &&
            ft_strcmp(lem->end_room->name, ptr_link->src) == 0))
        return (ptr_link->src);
	return (NULL);
}

static char		*valid_link_visited(char *cmp, t_link *ptr_link,
                                    t_room **origin, t_lem *lem)
{
    t_room		*ptr;
    char        *result;

    if (!(result = valid_link(cmp, ptr_link, origin, lem)))
        return (NULL);
	if (ft_strcmp(ptr_link->dest, result) == 0)
    {
        ptr = *origin;
        while (ft_strcmp(ptr_link->dest, ptr->name) != 0)
            ptr = ptr->next;
        ptr->visited = 1;
        return (ptr_link->dest);
    }
	if (ft_strcmp(ptr_link->src, result) == 0)
    {
        ptr = *origin;
        while (ft_strcmp(ptr_link->src, ptr->name) != 0)
            ptr = ptr->next;
        ptr->visited = 1;
        return (ptr_link->src);
    }
	return (NULL);
}

static void     linkers(t_lem *lem, t_path *ptr_path, t_path **append)
{
    t_link      *ptr_link;

    ptr_link = lem->link;
    while (ptr_link != NULL)
    {
        if (valid_link(ptr_path->ptr_end->line, ptr_link, &(lem->room), lem)
            != NULL)
        {
            copy_add_path(append, ptr_path,
                        valid_link_visited(ptr_path->ptr_end->line,
                        ptr_link, &(lem->room), lem));
        }
        ptr_link = ptr_link->next;
    }
}

t_path           *optimised_path(t_lem *lem, t_path *path)
{
    static int  loop = 0;
    t_path      *ptr_path;
    t_path      *append;

    ptr_path = path;
    append = NULL;
    if (loop >= lem->ants + lem->short_path_num)
        return (path);
    while (ptr_path != NULL)
    {
        if (ft_strcmp(ptr_path->ptr_end->line, lem->end_room->name) == 0)
        {
            ptr_path->end = 1;
            copy_path(&append, ptr_path);
            ptr_path = ptr_path->next;
            continue;
        }
        linkers(lem, ptr_path, &append);
        ptr_path = ptr_path->next;
    }
    loop++;
    free_path(&path);
    return (optimised_path(lem, append));
}

void            solver(t_lem *lem)
{
    t_path      *path;
    t_line      *ptr_line;
    t_path      *ptr_path;
    int         counter;
    int         only_one = 1;

    path = NULL;
    lem->left_ants = lem->ants;
    new_path(&path, lem->start_room->name);
    lem->start_room->visited = 1;
    ft_printf("total loop:%d\n", lem->left_ants + lem->short_path_num);
    // this should be less than 65507
    path = optimised_path(lem, path);
    sort_path(&path, lem);

    //debug tool
    t_path  *w;
    t_line  *e;
    w = path;
    while (w != NULL)
    {
            e = w->line;
            ft_printf("step:%dend:%d\t", w->step, w->end);
            while (e != NULL)
            {
                ft_printf("%s:%d---", e->line, e->ants);
                e = e->next;
            }
            ft_printf("\n");
        w = w->next;
    }
    //end debug

    lem->exited_ants = 0;
    while (lem->exited_ants != lem->ants)
    {
        counter = 1;
        while (lem->total_path + 1 != counter && lem->exited_ants != lem->ants)
        {
            ptr_path = path;
            while(ptr_path->order != counter)
                ptr_path = ptr_path->next;
            ft_printf("[#######]\n");
            if (lem->left_ants > 0 && ptr_path->end == 1)
            {
                ptr_line = ptr_path->line->next;
                while (ptr_line->next->next != NULL && ptr_line->ants > 0)
                {
            //        ptr_line->ant = ptr_line->next->ants;
                    ptr_line = ptr_line->next;
                }
                if (ptr_line->next->next == NULL && ptr_line->ants > 0)
                    (lem->exited_ants)++;
                else
                    ptr_line->ants = 1;
                (lem->left_ants)--;
            }
            else if (lem->left_ants == 0 && only_one == 1)
            {
                only_one = 0;
                while(counter != lem->total_path)
                        counter++;
            }
            else if (ptr_path->end == 1)
            {
                ptr_line = ptr_path->line->next;
                while (ptr_line->next->next != NULL && ptr_line->ants < 1)
                    ptr_line = ptr_line->next;
                if (ptr_line->next->next == NULL)
                {
                    ptr_line->ants = 0;
                    (lem->exited_ants)++;
                }
                else
                {
                    ptr_line->ants = 0;
                    if (ptr_line->next->ants == 1)
                        (lem->exited_ants)++;
                    else
                        ptr_line->next->ants = 1;
                }
            }
            counter++;
            //ptr_path = ptr_path->next;
            w = path;
            while (w != NULL)
            {
                e = w->line;
                ft_printf("step:%d\torder:%d\t", w->step, w->order);
                while (e != NULL)
                {
                    ft_printf("%s:%d---", e->line, e->ants);
                    e = e->next;
                }
                ft_printf("\n");
                w = w->next;
            }
            ft_printf("lem->exited_ants:%d\n", lem->exited_ants);
            sleep(1);
        }
    }
    free_path(&path);
}
