/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:21:40 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_data *data, char **args, int status)
{
	ft_free_arr(args);
	free_history(data->history);
	free_data(data);
	close_fd();
	exit(status);
}

void	exit_no_pipe(t_data *data, char **args, int *status)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!check_nb_args(args))
	{
		error_nb_args(status);
		return ;
	}
	if (args[1] && !is_numeric(args[1]))
		error_numeric(args[1], status);
	else if (args[1])
		*status = ft_atoi(args[1]);
	free_exit(data, args, *status);
}

void	exit_pipe(char **args, int *status)
{
	if (!check_nb_args(args))
	{
		error_nb_args(status);
		return ;
	}
	if (args[1] && !is_numeric(args[1]))
	{
		error_numeric(args[1], status);
		return ;
	}
	*status = ft_atoi(args[1]);
}

int	ft_exit(t_data *data, char **args)
{
	int	status;

	status = data->status;
	if (!data->cmd_lst->next)
		exit_no_pipe(data, args, &status);
	else
		exit_pipe(args, &status);
	ft_free_arr(args);
	return (status);
}
