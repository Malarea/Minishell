/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:34:22 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next(t_read *data)
{
	char	*next;
	int		pos;
	int		i;

	pos = data->pos;
	i = 0;
	next = malloc(ft_strlen(data->str) - pos + 1);
	if (!next)
		exit_parsing(data);
	while (data->str[pos])
	{
		next[i] = data->str[pos];
		pos++;
		i++;
	}
	next[i] = '\0';
	return (next);
}

char	*get_to_write(t_read *data)
{
	char	*to_write;
	int		pos;
	int		i;

	pos = data->pos;
	i = 1;
	to_write = malloc(ft_strlen(data->str) - data->pos + 2);
	if (!to_write)
		exit_parsing(data);
	to_write[0] = (char)data->c;
	while (data->str[pos])
	{
		to_write[i] = data->str[pos];
		pos++;
		i++;
	}
	to_write[i] = '\0';
	return (to_write);
}
