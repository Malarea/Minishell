/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:29:23 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We used getcwd that belong unistd.h
**	That contains the path of the working directory
*/
int	ft_pwd(char **args)
{
	int		status;
	char	cwd[PATH_MAX_B];

	status = 0;
	if (args[1] && is_option(args[1]))
		error_option(args[1], "pwd", &status);
	else if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory\n", \
		STDERR_FILENO);
		status = 1;
	}
	ft_free_arr(args);
	return (status);
}
