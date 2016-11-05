/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 06:46:40 by rmatos            #+#    #+#             */
/*   Updated: 2016/11/04 20:56:36 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_tmp(const int fd, char **buff)
{
	char	tmp[BUFF_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(*buff, '\n') == NULL)
	{
		bytes_read = read(fd, &tmp, BUFF_SIZE);
		tmp[bytes_read] = '\0';
		*buff = ft_strjoin(*buff, (const char *)tmp);
		ft_bzero(tmp, BUFF_SIZE);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char *buff;
	char		*str;

	if (fd < 0 || line == NULL || read(fd, buff, 0) == -1)
		return (-1);
	if (buff == NULL)
		buff = ft_strnew(BUFF_SIZE);
	read_tmp(fd, &buff);
	if ((str = ft_strchr(buff, '\n')))
	{
		*str = '\0';
		*line = buff;
		buff = str + 1;
		return (1);
	}
	*line = ft_strdup(buff);
	ft_strdel(&buff);
	return (*line[0] != '\0' ? 1 : 0);
}
