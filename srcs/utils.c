/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:34:00 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Utils file contains some useful functions
**	Like intro for showing the minishell in color
**	ft_write for write in file descriptor
**	Ws_fd for whitespace in file descriptor
*/
void	intro(void)
{
	ft_putstr_fd("\033[1;36mminishell\033[1;33m ✗\033[0m ", 1);
}

ssize_t	ft_write(int fd, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	ret = 0;
	if (!buf)
		return (ret);
	ret = write(fd, buf, nbyte);
	if (ret == ERROR)
		exit_strerror();
	return (ret);
}

void	ws_fd(size_t nb, int fd)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd(' ', fd);
		i++;
	}
}

char	*new_alloc(char *str, size_t size, size_t pos)
{
	char	*new;

	new = malloc(size + 1);
	if (!new)
		return (NULL);
	new = (char *)ft_memcpy(new, str, pos);
	new[size] = '\0';
	free_null((void **)&str);
	return (new);
}
