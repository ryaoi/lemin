/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:29:15 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/25 17:29:16 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void        new_path(t_path **begin, char *start)
{
    t_path  *new;
    t_path  *ptr;

    if (!(new = malloc(sizeof(t_path))))
        exit(EXIT_FAILURE);
    new->next = NULL;
    new->end = 0;
    if (!(new->line = malloc(sizeof(t_line))))
        exit(EXIT_FAILURE);
    new->line->line = ft_strdup(start);
    new->line->next = NULL;
    if (*begin == NULL)
		*begin = new;
	else
	{
		ptr = *begin;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
    new->ptr_end = new->line;
}

void        add_path(t_path **path, char *room)
{
    t_line  *ptr;

    ptr = (*path)->line;
    while (ptr != NULL)
        ptr = ptr->next;
    if (!(ptr = malloc(sizeof(t_line))))
        exit(EXIT_FAILURE);
    ptr->next = NULL;
    ptr->line = ft_strdup(room);
    (*path)->ptr_end = ptr;
}

static void copying(t_line *ptr_old, t_line *ptr, char *room,
                    t_path **ptr_path)
{
    while (ptr_old != NULL)
    {
        if (!((ptr) = malloc(sizeof(t_line))))
            exit(EXIT_FAILURE);
        (ptr)->next = NULL;
        (ptr)->line = ft_strdup(ptr_old->line);
        ft_printf("ptr->line:%s\n", (ptr)->line);
        (ptr) = (ptr)->next;
        ptr_old = ptr_old->next;
    }
    if (!((ptr) = malloc(sizeof(t_line))))
        exit(EXIT_FAILURE);
    ptr->line = ft_strdup(room);
    ft_printf("ptr->line (add):%s\n", ptr->line);
    ptr->next = NULL;
    (*ptr_path)->ptr_end = ptr;
}

static void copying_second(t_line *ptr_old, t_line *ptr, t_path **ptr_path)
{
    while (ptr_old != NULL)
    {
        if (!((ptr) = malloc(sizeof(t_line))))
            exit(EXIT_FAILURE);
        (ptr)->next = NULL;
        (ptr)->line = ft_strdup(ptr_old->line);
        (*ptr_path)->ptr_end = (ptr);
        (ptr) = (ptr)->next;
        ptr_old = ptr_old->next;
    }
}

void        copy_path(t_path **begin, t_path *old)
{
    t_path  *new;
    t_path  *ptr_path;
    t_line  *ptr;
    t_line  *ptr_old;

    if (!(new = malloc(sizeof(t_path))))
        exit(EXIT_FAILURE);
    new->next = NULL;
    new->line = NULL;
    new->end = 0;
    if (*begin == NULL)
        *begin = new;
    else
    {
        ptr_path = *begin;
        while (ptr_path->next != NULL)
            ptr_path = ptr_path->next;
        ptr_path->next = new;
    }
    ptr = new->line;
    ptr_old = old->line;
    copying_second(ptr_old, ptr, &new);
}

void        copy_add_path(t_path **begin, t_path *old, char *room)
{
    t_path  *new;
    t_path  *ptr_path;
    t_line  *ptr;
    t_line  *ptr_old;

    if (!(new = malloc(sizeof(t_path))))
        exit(EXIT_FAILURE);
    new->next = NULL;
    new->line = NULL;
    new->end = 0;
    if (*begin == NULL)
        *begin = new;
    else
    {
        ptr_path = *begin;
        while (ptr_path->next != NULL)
            ptr_path = ptr_path->next;
        ptr_path->next = new;
    }
    ptr = new->line;
    ptr_old = old->line;
    copying(ptr_old, ptr, room, &new);
}

void        free_path(t_path **origin)
{
    t_line  *ptr;
    t_path  *ptr_path;
    t_path  *ptr_path_next;
    t_line  *ptr_next;

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
