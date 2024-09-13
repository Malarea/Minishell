/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:20:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	exit_strerror(void)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	close_fd();
	exit(errno);
}

void	free_parsing(t_read *data)
{
	free_history(data->current);
	free_data(data->data);
	free_null((void **)&(data->str));
	free_null((void **)&data);
}

void	exit_parsing(t_read *data)
{
	free_parsing(data);
	exit_strerror();
}
