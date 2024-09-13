/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:28:49 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cwd(int *status)
{
	ft_putstr_fd("minishell: cd: error retrieving current directory: ", \
	STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	*status = 2;
}

int	check_stat_path(char *arg)
{
	struct stat	stat_buf;

	if (stat(arg, &stat_buf) == ERROR)
		return (0);
	if (stat_buf.st_mode & __S_IFDIR)
		return (1);
	return (0);
}

void	error_path(char *path, int *status)
{
	chdir(path);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	*status = 1;
}

void	error_cd_args(int *status)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	*status = 1;
}
