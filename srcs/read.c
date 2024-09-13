/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:01:03 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We manage end of file(CTRL+D) and key,check if input is valid
**	Add commands to the history and get the input
*/
void	management_eof(t_read *data)
{
	if (!data->str || data->str[0] == '\0')
	{
		free_parsing(data);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		close_fd();
		exit(0);
	}
}

int	is_valid_input(int c)
{
	if (32 <= c && c <= 127)
		return (1);
	return (0);
}

void	management_key(t_read *data)
{
	if (data->c == CTRL_D)
		management_eof(data);
	else if (data->c == RIGHT_KEY || data->c == LEFT_KEY)
		cursor_move(data);
	else if (data->c == UP_KEY || data->c == DOWN_KEY)
		history_navigation(data);
	else if (32 <= data->c && data->c <= 127)
		management_str(data);
}

void	add_cmd(t_read *data, t_history **history)
{
	int			fd;

	fd = open("/tmp/.minishell_history", \
	O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == ERROR)
		exit_strerror();
	if (data->str)
	{
		ft_putchar_fd('\n', fd);
		ft_putstr_fd(data->str, fd);
		replace_alloc(data->str, *history);
		push_front(new_elem_history(NULL), history);
	}
}

/*
**	Function who get the input while we writing,
**	And execute the command or quit if press a special key
**	(get status 130 if press CTRL+C) and use abort functions
** 	Otherwise we add commands to history
*/
t_read	*get_input(t_data *data)
{
	t_read		*data_parsing;

	data_parsing = init_read(data);
	if (!data_parsing)
	{
		free_history(data->history);
		exit_strerror();
	}
	while (1)
	{
		data_parsing->c = get_last_char(data_parsing);
		if (data_parsing->c == NL_KEY || data_parsing->c == CTRL_C)
		{
			if (data_parsing->c == CTRL_C)
				abort_cmd(data_parsing, &(data->status));
			else if (data_parsing->c == NL_KEY)
				add_cmd(data_parsing, &(data->history));
			break ;
		}
		else
			management_key(data_parsing);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (data_parsing);
}
