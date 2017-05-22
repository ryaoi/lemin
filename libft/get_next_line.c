/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:44:47 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/11 20:05:47 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			add_chunk(char **line, char *buff, size_t size)
{
	char			*tmp;
	char			*ptr_tmp;

	if (*line == NULL)
		*line = ft_strnew(1);
	tmp = ft_strsub(buff, 0, size);
	ptr_tmp = *line;
	*line = ft_strjoin(*line, tmp);
	free(ptr_tmp);
	free(tmp);
}

static void			parse(const int fd, char **line, t_fd_buff *fd_buff)
{
	unsigned int	begin_pos;

	begin_pos = fd_buff->pos;
	while (fd_buff->buff[fd_buff->pos] != '\n' && fd_buff->n != 0)
	{
		if (--(fd_buff->n) == 0)
		{
			add_chunk(line, fd_buff->buff + begin_pos,
						fd_buff->pos - begin_pos + 1);
			fd_buff->pos = 0;
			begin_pos = fd_buff->pos;
			fd_buff->n = read(fd, fd_buff->buff, BUFF_SIZE);
		}
		else
			(fd_buff->pos)++;
	}
	if (fd_buff->n != 0)
	{
		add_chunk(line, fd_buff->buff + begin_pos, fd_buff->pos - begin_pos);
		--(fd_buff->n);
		++(fd_buff->pos);
	}
}

static t_fd_buff	*find_fd_buff(t_list *lst, int fd)
{
	while (lst != NULL)
	{
		if (((t_fd_buff *)lst->content)->fd == fd)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

static t_fd_buff	*select_fd_buff(t_list **lst, int fd)
{
	t_fd_buff		*new_fd_buff;
	t_fd_buff		*ptr;
	t_list			*new_lst;

	if ((ptr = find_fd_buff(*lst, fd)) != NULL)
		return (ptr);
	if ((new_fd_buff = (t_fd_buff *)malloc(sizeof(t_fd_buff))) == NULL)
		return (NULL);
	new_fd_buff->fd = fd;
	new_fd_buff->pos = 0;
	new_fd_buff->n = 0;
	new_fd_buff->buff = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (new_fd_buff->buff == NULL)
		return (NULL);
	if ((new_lst = ft_lstnew(new_fd_buff, sizeof(t_list))) == NULL)
		return (NULL);
	ft_lstadd(lst, new_lst);
	free(new_fd_buff);
	return ((*lst)->content);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	t_fd_buff		*fd_buff;

	*line = NULL;
	fd_buff = select_fd_buff(&lst, fd);
	if (fd_buff == NULL)
		return (-1);
	if (fd_buff->n <= 0)
	{
		if ((fd_buff->n = read(fd, fd_buff->buff, BUFF_SIZE)) <= 0)
			return (fd_buff->n);
		else
			fd_buff->pos = 0;
	}
	parse(fd, line, fd_buff);
	return (1);
}
