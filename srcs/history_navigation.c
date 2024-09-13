/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_navigation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:15:02 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_up(t_read *data)
{
	if (data->current->next)
	{
		if (data->str)
			replace_alloc(data->str, data->current);
		wipe_and_replace(data, data->current->next);
		data->current = data->current->next;
	}
	return ;
}

void	go_down(t_read *data)
{
	if (data->current->prev)
	{
		if (data->str)
			replace_alloc(data->str, data->current);
		wipe_and_replace(data, data->current->prev);
		data->current = data->current->prev;
	}
}

void	history_navigation(t_read *data)
{
	if (data->c == UP_KEY)
		go_up(data);
	else if (data->c == DOWN_KEY)
		go_down(data);
}
