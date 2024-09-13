/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:05:02 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We get each history lines and create .minishell_history
*/
int	get_nb_lines(void)
{
	char	*line;
	int		fd;
	int		nb;
	int		ret;

	line = NULL;
	nb = 0;
	fd = open("/tmp/.minishell_history", O_RDONLY | O_CREAT, 0666);
	if (fd == ERROR)
		exit_strerror();
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		nb++;
		free_null((void **)&line);
		ret = get_next_line(fd, &line);
	}
	free_null((void **)&line);
	if (close(fd) == ERROR || ret == ERROR)
		exit_strerror();
	if (nb == 0)
		return (nb);
	return (nb + 1);
}

int	go_to_line(int nb_lines, int max)
{
	int		fd;
	char	*line;
	int		ret;
	int		count;

	fd = open("/tmp/.minishell_history", O_RDONLY, 0666);
	if (fd == ERROR)
		exit_strerror();
	line = NULL;
	ret = get_next_line(fd, &line);
	count = 1;
	while (count < nb_lines - max && ret > 0)
	{
		free_null((void **)&line);
		ret = get_next_line(fd, &line);
		count++;
	}
	free_null((void **)&line);
	if (ret == ERROR)
		exit_strerror();
	return (fd);
}

t_history	*get_list(int fd, int max)
{
	t_history	*history;

	history = NULL;
	fill_history(fd, max, &history);
	if (!history)
		history = new_elem_history(NULL);
	return (history);
}

/*
** Current element of history become the previous
*/
void	flip_history(t_history **history)
{
	t_history	*current;

	current = *history;
	while (current->prev)
		current = current->prev;
	*history = current;
}

t_history	*get_history(int max)
{
	t_history	*history;
	int			fd;
	int			nb_lines;

	nb_lines = get_nb_lines();
	fd = go_to_line(nb_lines, max);
	if (fd < 0)
		exit_strerror();
	history = get_list(fd, max);
	flip_history(&history);
	if (history->cmd)
		push_front(new_elem_history(NULL), &history);
	return (history);
}
