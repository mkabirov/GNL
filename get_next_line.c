/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabirov <mkabirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:35:46 by mkabirov          #+#    #+#             */
/*   Updated: 2019/09/07 22:55:27 by mkabirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_line(char **save, char **str, char **line, const int fd)
{
	char			*point_nl;

	if (*str[fd] != '\0')
	{
		if (!(ft_strchr(str[fd], '\n')))
		{
			*save = ft_strdup(str[fd]);
			free(str[fd]);
			str[fd] = NULL;
		}
		else if ((point_nl = ft_strchr(str[fd], '\n')))
		{
			*point_nl = '\0';
			*save = ft_strdup(str[fd]);
			point_nl++;
			ft_strcpy(str[fd], point_nl);
			*line = *save;
			return (1);
		}
	}
	return (0);
}

int					save_buf(char **save, char *buf, char **str, const int fd)
{
	char			*point_nl;
	char			*tmp;

	if ((point_nl = ft_strchr(buf, '\n')))
	{
		*point_nl = '\0';
		str[fd] = ft_strdup(++point_nl);
		if (*save != NULL)
		{
			tmp = *save;
			*save = ft_strjoin(*save, buf);
			free(tmp);
		}
		(*save == NULL) ? (*save = ft_strdup(buf)) : 0;
		return (1);
	}
	if (*save != NULL)
	{
		tmp = *save;
		*save = ft_strjoin(*save, buf);
		free(tmp);
	}
	else
		*save = ft_strdup(buf);
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static char		*str[FDM];
	char			*save;

	if (fd < 0 || !line || (read(fd, buf, 0) < 0) || fd > FDM || BUFF_SIZE <= 0)
		return (-1);
	save = NULL;
	if ((str[fd] != NULL) && (get_line(&save, str, line, fd) == 1))
		return (1);
	ret = 1;
	while (ret)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		else if (ret == 0)
			return ((*line = save) == NULL) ? 0 : 1;
		buf[ret] = '\0';
		if (save_buf(&save, buf, str, fd))
		{
			*line = save;
			return (1);
		}
	}
	return (1);
}
