/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:14:12 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Delete a character
*/
char	*new_del(t_read *data)
{
	char	*new;
	char	*prev;
	char	*next;

	next = get_next(data);
	if (!next)
		exit_parsing(data);
	prev = new_alloc(data->str, data->pos - 1, data->pos - 1);
	if (!prev)
		exit_parsing(data);
	new = ft_strjoin(prev, next);
	cursor_left(1);
	ws_fd(ft_strlen(next) + 1, STDIN_FILENO);
	cursor_left(ft_strlen(next) + 1);
	ft_write(STDIN_FILENO, next, ft_strlen(next));
	cursor_left(ft_strlen(next));
	free_null((void **)&prev);
	free_null((void **)&next);
	return (new);
}

/*
**	Add a character if,
**	The cursor is not at the end of the string
*/
char	*new_insert(t_read *data)
{
	char	*prev;
	char	*to_write;
	char	*new;

	to_write = get_to_write(data);
	prev = new_alloc(data->str, data->pos, data->pos);
	if (!prev)
		exit_parsing(data);
	new = ft_strjoin(prev, to_write);
	ft_write(STDIN_FILENO, to_write, ft_strlen(to_write));
	cursor_left(ft_strlen(to_write) - 1);
	free_null((void **)&prev);
	free_null((void **)&to_write);
	return (new);
}

/*
**	Add a character if
**	The cursor is at the end of the string
*/
char	*new_char(t_read *data)
{
	char	*new;

	new = new_alloc(data->str, data->pos + 1, data->pos);
	if (!new)
		exit_parsing(data);
	new[data->pos] = (char)data->c;
	ft_write(STDIN_FILENO, &data->c, sizeof(data->c));
	return (new);
}

/*
**	Manage the string,
**	Add or delete character in the prompt
*/
void	management_str(t_read *data)
{
	if (data->c == DEL_KEY)
	{
		if (data->pos > 0)
		{
			data->str = new_del(data);
			(data->pos)--;
			(data->len)--;
		}
	}
	else
	{
		if (data->pos < data->len)
			data->str = new_insert(data);
		else
			data->str = new_char(data);
		(data->pos)++;
		(data->len)++;
	}
}
