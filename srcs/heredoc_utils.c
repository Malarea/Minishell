/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:15:22 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_heredoc(t_read *heredoc)
{
	free_history(heredoc->data->history);
	free_data(heredoc->data);
	free_null((void **)&heredoc->str);
	free_null((void **)&heredoc);
	ft_putstr_fd("^C\n", STDERR_FILENO);
	unlink(".heredoc");
	close_fd();
	exit(130);
}

void	eof_heredoc(t_read *heredoc, t_redir *redir)
{
	if (!heredoc->str || heredoc->str[0])
	{
		ft_putstr_fd("minishell: warning: EOF, wanted ('", STDERR_FILENO);
		ft_putstr_fd(redir->word, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		free_history(heredoc->data->history);
		free_data(heredoc->data);
		free_null((void **)&heredoc->str);
		free_null((void **)&heredoc);
		unlink(".heredoc");
		close_fd();
		exit(0);
	}
}

void	input_heredoc(t_read *heredoc, t_redir *redir)
{
	if (heredoc->c == CTRL_D)
		eof_heredoc(heredoc, redir);
	else if (heredoc->c == RIGHT_KEY || heredoc->c == LEFT_KEY)
		cursor_move(heredoc);
	else if (32 <= heredoc->c && heredoc->c <= 127)
		management_str(heredoc);
}
