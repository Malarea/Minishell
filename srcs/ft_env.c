/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:25:47 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We get env var,we check errors (options,args)
**	After we putstr each var
**	We free it
*/
int	ft_env(t_data *data, char **args)
{
	int		status;
	char	**env;
	int		i;

	status = 0;
	env = get_env(data);
	i = 0;
	if (args[1] && is_option(args[1]))
		error_option(args[1], "env", &status);
	else if (args[1])
		error_arg(args[1], "env", &status);
	else
	{
		while (env[i])
		{
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			i++;
		}
	}
	ft_free_arr(args);
	ft_free_arr(env);
	return (status);
}
