/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:05:00 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_file(char *word)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	error_opening(t_data *data, int flag)
{
	if (flag == BUILTIN)
	{
		data->status = 1;
		return ;
	}
	free_history(data->history);
	free_data(data);
	close_fd();
	exit(1);
}

int	get_infile(t_data *data, t_cmd *cmd)
{
	int		fd;
	t_redir	*current;

	fd = NO_FD;
	current = cmd->in_lst;
	while (current)
	{
		if (fd != NO_FD)
			close(fd);
		if (current->flag == SIMPLE_LEFT)
			fd = open(current->word, O_RDONLY);
		else if (current->flag == DOUBLE_LEFT)
			fd = get_heredoc(data, current);
		if (fd == ERROR)
		{
			error_file(current->word);
			return (fd);
		}
		current = current->next;
	}
	return (fd);
}

int	get_outfile(t_cmd *cmd)
{
	int		fd;
	t_redir	*current;

	fd = NO_FD;
	current = cmd->out_lst;
	while (current)
	{
		if (fd != NO_FD)
			close(fd);
		if (current->flag == SIMPLE_RIGHT)
			fd = open(current->word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (current->flag == DOUBLE_RIGHT)
			fd = open(current->word, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == ERROR)
		{
			error_file(current->word);
			return (fd);
		}
		current = current->next;
	}
	return (fd);
}

int	open_files(t_data *data, t_cmd *cmd, t_run *run, int flag)
{
	run->fd_in = get_infile(data, cmd);
	if (run->fd_in == ERROR)
	{
		error_opening(data, flag);
		return (ERROR);
	}
	run->fd_out = get_outfile(cmd);
	if (run->fd_out == ERROR)
	{
		error_opening(data, BUILTIN);
		return (ERROR);
	}
	return (SUCCESS);
}
