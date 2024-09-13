/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:35:04 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*new_elem_history(char *line)
{
	t_history	*elem;

	elem = malloc(sizeof(t_history));
	if (!elem)
		exit_strerror();
	elem->cmd = line;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	push_front(t_history *elem, t_history **history)
{
	(*history)->prev = elem;
	elem->next = *history;
	*history = elem;
}

void	append_history(t_history **history, char *line)
{
	t_history	*current;
	t_history	*new;

	if (!(*history))
		*history = new_elem_history(line);
	else
	{
		current = *history;
		while (current->prev)
			current = current->prev;
		new = new_elem_history(line);
		new->next = current;
		current->prev = new;
	}
}

void	free_history(t_history *elem)
{
	t_history	*next;

	while (elem->prev)
		elem = elem->prev;
	while (elem)
	{
		next = elem->next;
		free_null((void **)&(elem->cmd));
		free_null((void **)&elem);
		elem = next;
	}
}

void	fill_history(int fd, int max, t_history **history)
{
	char	*line;
	int		ret;
	int		i;

	line = NULL;
	ret = get_next_line(fd, &line);
	i = 0;
	while (i < max && ret > 0)
	{
		if (line && line[0])
		{
			append_history(history, line);
			i++;
		}
		else
			free_null((void **)&line);
		ret = get_next_line(fd, &line);
	}
	if (line && line[0])
		append_history(history, line);
	else
		free_null((void **)&line);
	if (ret == ERROR)
		exit_strerror();
}
