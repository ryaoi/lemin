/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:51:11 by ryaoi             #+#    #+#             */
/*   Updated: 2017/05/11 20:00:06 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 1

typedef struct		s_fd_buff
{
	int				fd;
	unsigned int	pos;
	ssize_t			n;
	char			*buff;
}					t_fd_buff;

int					get_next_line(int const fd, char **line);

#endif
