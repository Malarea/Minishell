/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:07:09 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/15 17:13:46 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Our only global variable
*/
int		g_pid;

/*
**	We check if tmp directory was created
*/
void	check_tmp_dir(void)
{
	DIR	*dir;

	dir = opendir("/tmp");
	if (dir == NULL)
	{
		ft_putstr_fd("minishell: '/tmp' was not found\n", STDERR_FILENO);
		close_fd();
		exit(1);
	}
	closedir(dir);
}

/*
**	Initialize data struct
*/
t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_strerror();
	data->var_lst = get_var_lst(data, env);
	data->str = NULL;
	data->status = 0;
	data->cmd_lst = NULL;
	data->history = get_history(20);
	return (data);
}

/*
**	Check if the signal doesnt contains errors
**	Start the intro (who is the minishell str in blue)
**	We get the input we store it in data,free it and run data
*/
void	minishell(char **env)
{
	t_data		*data;
	t_read		*data_parsing;

	check_tmp_dir();
	data = init_data(env);
	if (signal(SIGINT, stop_process) == SIG_ERR)
		exit_custom(data, NULL, AUTO);
	if (signal(SIGQUIT, stop_process) == SIG_ERR)
		exit_custom(data, NULL, AUTO);
	while (1)
	{
		intro();
		data_parsing = get_input(data);
		data->str = data_parsing->str;
		free_null((void **)&data_parsing);
		if (data->str)
			run(data);
		free_null((void **)&data->var_lst->val);
		data->var_lst->val = ft_itoa(data->status);
	}
}
