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

static char		*valid_link(char *cmp, t_link *ptr_link, t_room *origin)
{
    t_room		*ptr;

	if ((ft_strcmp(cmp, ptr_link->src) == 0 &&
		check_name_visited(ptr_link->dest, origin) == 0))
    {
        ptr = origin;
        while (ft_strcmp(cmp, ptr->name) != 0)
            ptr = ptr->next;
        ptr->visited = 1;
        return (ptr_link->dest);
    }
	if ((ft_strcmp(cmp, ptr_link->dest) == 0 &&
		check_name_visited(ptr_link->src, origin) == 0))
    {
        ptr = origin;
        while (ft_strcmp(cmp, ptr->name) != 0)
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
        wolo = wala->ptr_end;
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
            copy_path(&append, ptr_path);
            ptr_path->end = 1;
            ptr_path = ptr_path->next;
            ft_printf("arrived to the end.\n");
            continue;
        }
        ptr_link = lem->link;
        while (ptr_link != NULL)
        {
            if (valid_link(ptr_path->ptr_end->line, ptr_link, lem->room) != NULL)
                copy_add_path(&append, ptr_path, valid_link(ptr_path->ptr_end->line,
                            ptr_link, lem->room));
            ptr_link = ptr_link->next;
        }
        ptr_path = ptr_path->next;
    }
    loop++;
    //debug
    wala = append;
    ft_printf("|||||||||||||||\nstep:%d\n", loop);
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
    ft_printf("|||||||||||||||\n");

    //end debug
    ft_printf("recursion!\n");
    optimised_path(lem, append);
    free_path(&path);
    return (NULL);
}

void            solver(t_lem *lem)
{
    t_path      *path;
//    int         i;
//    int         size;

    ft_printf("solver!\n");
    path = NULL;
    lem->left_ants = lem->ants;
    new_path(&path, lem->start_room->name);
    ft_printf("total loop:%d\n", lem->ants + lem->short_path_num - 1);
    path = optimised_path(lem, path);
    if (path == NULL)
    {
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
