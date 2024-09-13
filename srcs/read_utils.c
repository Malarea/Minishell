/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:04:12 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_read	*init_read(t_data *data)
{
	t_read	*data_parsing;

	data_parsing = malloc(sizeof(t_read));
	if (!data_parsing)
	{
		free_history(data->history);
		exit_strerror();
	}
	data_parsing->c = 0;
	data_parsing->pos = 0;
	data_parsing->len = 0;
	data_parsing->current = data->history;
	data_parsing->str = NULL;
	data_parsing->data = data;
	return (data_parsing);
}

void	abort_cmd(t_read *data, int *status)
{
	ft_putstr_fd("^C", STDOUT_FILENO);
	free_null((void **)&(data->str));
	*status = 130;
}

int	ft_getc(t_read *data)
{
	int	c;

	c = 0;
	if (read(0, &c, sizeof(c)) < 0)
		exit_parsing(data);
	return (c);
}

int	get_last_char(t_read *data)
{
	int				c;
	struct termios	oterm;
	struct termios	term;

	tcgetattr(0, &oterm);
	ft_memcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	c = ft_getc(data);
	tcsetattr(0, TCSANOW, &oterm);
	return (c);
}
