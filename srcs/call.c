/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_close(int new_fd, int old_fd)
{
	dup2(new_fd, old_fd);
	close(new_fd);
}

/*
**	Check if the cmd is a builtin
*/
int	is_builtin(t_data *data, t_cmd *cmd)
{
	char	**args;

	if (!cmd->args)
		return (0);
	args = ft_split(cmd->args, ' ');
	if (!args)
		exit_custom(data, NULL, AUTO);
	if (!ft_strncmp("echo", args[0], 5) || \
	!ft_strncmp("cd", args[0], 3) || \
	!ft_strncmp("pwd", args[0], 4) || \
	!ft_strncmp("export", args[0], 7) || \
	!ft_strncmp("unset", args[0], 6) || \
	!ft_strncmp("env", args[0], 4) || \
	!ft_strncmp("exit", args[0], 5))
	{
		ft_free_arr(args);
		return (1);
	}
	ft_free_arr(args);
	return (0);
}

int	call_setup(t_data *data, t_cmd *cmd, t_run run, int flag)
{
	if (open_files(data, cmd, &run, flag) == ERROR)
		return (ERROR);
	if (run.fd_pipe != NO_FD)
		dup2_close(run.fd_pipe, STDIN_FILENO);
	if (cmd->next)
		dup2_close(run.fd[1], STDOUT_FILENO);
	else
	{
		close(run.fd[0]);
		close(run.fd[1]);
	}
	if (run.fd_in != NO_FD)
		dup2_close(run.fd_in, STDIN_FILENO);
	if (run.fd_out != NO_FD)
		dup2_close(run.fd_out, STDOUT_FILENO);
	return (SUCCESS);
}

/*
**	Check each builtin and run the function that belongs to it
*/
int	call_builtin(t_data *data, t_cmd *cmd, t_run run)
{
	char	**args;

	if (!cmd->args)
		return (0);
	if (call_setup(data, cmd, run, BUILTIN) == ERROR)
		return (data->status);
	args = get_args(data, cmd);
	if (!ft_strncmp("echo", args[0], 5))
		return (ft_echo(args));
	if (!ft_strncmp("cd", args[0], 3))
		return (ft_cd(data, args));
	if (!ft_strncmp("pwd", args[0], 4))
		return (ft_pwd(args));
	if (!ft_strncmp("export", args[0], 7))
		return (ft_export(data, args));
	if (!ft_strncmp("unset", args[0], 6))
		return (ft_unset(data, args));
	if (!ft_strncmp("env", args[0], 4))
		return (ft_env(data, args));
	if (!ft_strncmp("exit", args[0], 5))
		return (ft_exit(data, args));
	return (0);
}

/*
**	Execute the corresponding binary file for the cmd called
*/
void	call_execve(t_data *data, t_cmd *cmd, t_run run)
{
	char	**args;
	char	**argv;
	char	**env;

	args = get_args(data, cmd);
	argv = get_argv(data, args);
	env = get_env(data);
	call_setup(data, cmd, run, FORK);
	if (argv)
		if (execve(argv[0], argv, env) == ERROR)
			exit_custom(data, NULL, AUTO);
	ft_free_arr(env);
	free_history(data->history);
	free_data(data);
	exit(0);
}
