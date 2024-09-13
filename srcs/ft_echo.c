/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:25:41 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function is used to echo
**	Check if there an option -n is used if it is we skip a newline
*/
int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
		;
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
	ft_free_arr(args);
	return (0);
}
