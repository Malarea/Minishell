/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:29:44 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

/*
**	We manage the cursor for move it, 
**	If it's left we decrement if it's right we increment
**	For recognize the key pressed, 
**	We used keycode that have been define in minishell.h
*/
void	cursor_left(int iter)
{
	int	i;

	i = 0;
	while (i < iter)
	{
		ft_write(0, "\033[1D", 4);
		i++;
	}
}

void	cursor_right(int iter)
{
	int	i;

	i = 0;
	while (i < iter)
	{
		ft_write(0, "\033[1C", 4);
		i++;
	}
}

void	cursor_move(t_read *data)
{
	if (data->c == RIGHT_KEY)
	{
		if (data->pos < data->len)
		{
			cursor_right(1);
			(data->pos)++;
		}
	}
	else if (data->c == LEFT_KEY)
	{
		if (data->pos > 0)
		{
			cursor_left(1);
			(data->pos)--;
		}
	}
}
