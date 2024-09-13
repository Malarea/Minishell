/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:25:42 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) > 3)
		return (0);
	if (!ft_isdigit(arg[i]))
		return (0);
	if (ft_atoi(arg) > 256)
		return (0);
	return (1);
}

int	check_nb_args(char **args)
{
	if (args[1] && is_numeric(args[1]) && args[2])
		return (0);
	return (1);
}

void	error_numeric(char *arg, int *status)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": valid numeric argument required\n", STDERR_FILENO);
	*status = 2;
}

void	error_nb_args(int *status)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", \
	STDERR_FILENO);
	*status = 1;
}
