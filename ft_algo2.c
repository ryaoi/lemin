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

static char		*valid_link(char *cmp, t_link *ptr_link, t_room **origin, t_lem *lem)
{
    t_room		*ptr;

    ft_printf("cmp:%s\t%s-%s\n", cmp, ptr_link->src, ptr_link->dest);
	if ((ft_strcmp(cmp, ptr_link->src) == 0 &&
		check_name_visited(ptr_link->dest, *origin) == 0)
        || (ft_strcmp(cmp, ptr_link->src) == 0 &&
            ft_strcmp(lem->end_room->name, ptr_link->dest) == 0))
    {
        ptr = *origin;
        ft_printf("ptr_link->dest:%s\n", ptr_link->dest);
        while (ft_strcmp(ptr_link->dest, ptr->name) != 0)
            ptr = ptr->next;
        return (ptr_link->dest);
    }
	if ((ft_strcmp(cmp, ptr_link->dest) == 0 &&
		check_name_visited(ptr_link->src, *origin) == 0)
        || (ft_strcmp(cmp, ptr_link->dest) == 0 &&
            ft_strcmp(lem->end_room->name, ptr_link->src) == 0))
    {
        ptr = *origin;
        ft_printf("ptr_link->src is:%s\n", ptr_link->src);
        while (ft_strcmp(ptr_link->src, ptr->name) != 0)
            ptr = ptr->next;
        return (ptr_link->src);
    }
    ft_printf("---returned NULL!\n");
	return (NULL);
}

static char		*valid_link_visited(char *cmp, t_link *ptr_link, t_room **origin,
                                    t_lem *lem)
{
    t_room		*ptr;

	if ((ft_strcmp(cmp, ptr_link->src) == 0 &&
		check_name_visited(ptr_link->dest, *origin) == 0)
        || (ft_strcmp(cmp, ptr_link->src) == 0 &&
            ft_strcmp(lem->end_room->name, ptr_link->dest) == 0))
    {
        ptr = *origin;
        ft_printf("ptr_link->dest:%s\n", ptr_link->dest);
        while (ft_strcmp(ptr_link->dest, ptr->name) != 0)
            ptr = ptr->next;
        ptr->visited = 1;
        return (ptr_link->dest);
    }
	if ((ft_strcmp(cmp, ptr_link->dest) == 0 &&
		check_name_visited(ptr_link->src, *origin) == 0)
        || (ft_strcmp(cmp, ptr_link->dest) == 0 &&
            ft_strcmp(lem->end_room->name, ptr_link->src) == 0))
    {
        ptr = *origin;
        ft_printf("ptr_link->src is:%s\n", ptr_link->src);
        while (ft_strcmp(ptr_link->src, ptr->name) != 0)
            ptr = ptr->next;
        ptr->visited = 1;
        return (ptr_link->src);
    }
	return (NULL);
}

t_path           *optimised_path(t_lem *lem, t_path *path)
{
    static int  loop = 0;
    t_link      *ptr_link;
    t_path      *ptr_path;
    t_path      *append;

    ptr_path = path;
    append = NULL;

    //debug tool
    t_path     *wala;
    t_line      *wolo;

    wala = path;
    ft_printf("+--------------+\nstep:%d\n", loop);
    while (wala != NULL)
    {
        wolo = wala->line;
        while (wolo != NULL)
        {
            ft_printf("%s-", wolo->line);
            wolo = wolo->next;
        }
        ft_printf("\n");
        wala = wala->next;
    }
    ft_printf("+--------------+\n");
    //end debug tool
    if (loop > lem->ants + lem->short_path_num - 1)
    {
        ft_printf("finished looping\n");
        return (path);
    }
    while (ptr_path != NULL)
    {
        if (ft_strcmp(ptr_path->ptr_end->line, lem->end_room->name) == 0)
        {
            ptr_path->end = 1;
            copy_path(&append, ptr_path);
            ptr_path = ptr_path->next;
            continue;
        }
        ptr_link = lem->link;
        while (ptr_link != NULL)
        {
            if (valid_link(ptr_path->ptr_end->line, ptr_link, &(lem->room), lem) != NULL)
            {
                copy_add_path(&append, ptr_path, valid_link_visited(ptr_path->ptr_end->line,
                            ptr_link, &(lem->room), lem));
            }
            ptr_link = ptr_link->next;
        }
        ptr_path = ptr_path->next;
    }
    loop++;
    free_path(&path);
    optimised_path(lem, append);
    return (NULL);
}

void            solver(t_lem *lem)
{
    t_path      *path;

    path = NULL;
    lem->left_ants = lem->ants;
    new_path(&path, lem->start_room->name);
    lem->start_room->visited = 1;
    ft_printf("total loop:%d\n", lem->ants + lem->short_path_num - 1);
    path = optimised_path(lem, path);
    if (path == NULL)
    {	//debug tool
		t_room *ptr;
		for (ptr = lem->room;ptr != NULL;ptr = ptr->next)
			ft_printf("room:%-10s\tstart:%d\tend:%d\tvisited:%d\n", ptr->name, ptr->start, ptr->end, ptr->visited);
		//debug end
        ft_printf("got null and this is not good\n");
        exit (0);
    }
    //debug
    t_path  *ptr;
    t_line  *ptr_line;
    ptr = path;
    while (ptr != NULL)
    {
        if (ptr->end == 1)
        {
            ptr_line = ptr->line;
            while (ptr_line != NULL)
            {
                ft_printf("%s---", ptr_line->line);
                ptr_line = ptr_line->next;
            }
            ft_printf("\n");
        }
        ptr = ptr->next;
    }
    //end debug
    //checker if theres any room that are doubled
}
