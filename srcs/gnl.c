/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:05:02 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	get_len_line(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = 0;
	while (line[len])
		len++;
	return (len);
}

int	empty_line(char **line)
{
	*line = malloc(sizeof(char));
	if (!*line)
		return (ERROR);
	**line = '\0';
	return (0);
}

int	fill_line_nl(char **line)
{
	if (!*line)
	{
		if (empty_line(line) == ERROR)
			return (ERROR);
	}
	return (NL);
}

int	fill_line(char **line, char *buf)
{
	char	*new_line;
	int		len_line;
	int		i;

	i = 0;
	if (*buf == '\n')
		return (fill_line_nl(line));
	len_line = get_len_line(*line);
	new_line = malloc(sizeof(char) * (len_line + 2));
	if (!new_line)
		return (ERROR);
	while (i < len_line)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	new_line[i] = *buf;
	new_line[i + 1] = '\0';
	free(*line);
	*line = new_line;
	return (NO_NL);
}

int	get_next_line(int fd, char **line)
{
	char		buf[2];
	ssize_t		b_read;
	int			ret;

	*line = NULL;
	b_read = read(fd, buf, 1);
	if (b_read == ERROR)
		return (ERROR);
	buf[1] = '\0';
	while (b_read)
	{
		ret = fill_line(line, buf);
		if (ret == ERROR || ret == NL)
			return (ret);
		b_read = read(fd, buf, 1);
		if (b_read == ERROR)
			return (ERROR);
		buf[1] = '\0';
	}
	if (!*line)
	{
		if (empty_line(line) == ERROR)
			return (ERROR);
	}
	return (EOF_READ);
}
