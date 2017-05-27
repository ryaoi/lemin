/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:16:33 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/27 03:40:22 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		new_line(t_line **begin, char *line)
{
	t_line	*new;
	t_line	*ptr;

	if (!(new = malloc(sizeof(t_line))))
		exit(EXIT_FAILURE);
	new->line = ft_strdup(line);
	new->next = NULL;
	if (*begin == NULL)
		*begin = new;
	else
	{
		ptr = *begin;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void		free_line(t_line **begin)
{
	t_line	*ptr;
	t_line	*next;

	ptr = *begin;
	while (ptr != NULL)
	{
		next = ptr->next;
		free(ptr->line);
		free(ptr);
		ptr = next;
	}
}

void		print_all_line(t_line *sentence)
{
	t_line	*ptr;

	ptr = sentence;
	while (ptr != NULL)
	{
		ft_printf("%s\n", ptr->line);
		ptr = ptr->next;
	}
}
