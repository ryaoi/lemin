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

    path = NULL;
    lem->left_ants = lem->ants;
    lem->exited_ants = 0;
    new_path(&path, lem->start_room->name);
    lem->start_room->visited = 1;
    // this should be less than 65507
    path = optimised_path(lem, path);
    //debug tool
    t_path  *w;
    t_line  *e;
    w = path;
    while (w != NULL)
    {
            e = w->line;
            ft_printf("step:%d etape:%d\t", w->step, w->step);
            while (e != NULL)
            {
                if (e == w->line)
                    ft_printf("%s(%d)---", e->line, lem->ants);
                else if (e->next != NULL)
                    ft_printf("%s(%d)---", e->line, e->ants);
                else
                    ft_printf("%s(%d)", e->line, 0);
                e = e->next;
            }
            ft_printf("\n");
        w = w->next;
    }
    //end debug
    ft_printf("sort-----------");
    sort_path(&path, lem);
    ft_printf("sorted\n");
    lem->turn = 1;
    while (lem->exited_ants != lem->ants)
    {
        ft_printf("[turn:%d]\n", lem->turn);
        counter = 1;
        while (lem->total_path + 1 != counter && lem->exited_ants != lem->ants)
        {
            ptr_path = path;
            while(ptr_path->order != counter)
                ptr_path = ptr_path->next;
            //ft_printf("[path info]\n");
            if (lem->left_ants > 0 && ptr_path->end == 1)
            {
                ptr_line = ptr_path->line->next;
                while (ptr_line->next->next != NULL && ptr_line->ants > 0)
                {
                    ptr_line = ptr_line->next;
                }
                if (ptr_line->next->next == NULL && ptr_line->ants > 0)
                    (lem->exited_ants)++;
                else
                    ptr_line->ants = 1;
                (lem->left_ants)--;
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
                    ptr_line = ptr_line->next;
                    while (ptr_line->next->next != NULL && ptr_line->ants > 0)
                        ptr_line = ptr_line->next;
                    if (ptr_line->next->next == NULL)
                        (lem->exited_ants)++;
                    else
                        ptr_line->ants = 1;
                }
            }
            counter++;
            //debug
            w = path;
            while (w != NULL)
            {
                e = w->line;
                ft_printf("step:%d\torder:%d\t", w->step, w->order);
                while (e != NULL)
                {
                    if (e == w->line)
                        ft_printf("%s(%d)---", e->line, lem->left_ants);
                    else if (e->next != NULL)
                        ft_printf("%s(%d)---", e->line, e->ants);
                    else
                        ft_printf("%s(%d)", e->line, lem->exited_ants);
                    e = e->next;
                }
                ft_printf("\n");
                w = w->next;
            }
            sleep(1);
            // end debug
        }
        //print the map Lx-y
        (lem->turn)++;
    }
    ft_printf("[final result:%d]\n", lem->turn - 1);
    free_path(&path);
}
