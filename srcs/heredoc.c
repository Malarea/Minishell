/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:04:02 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	The heredoc is used to declare a string of characters in a shell command
**	The most common syntax is << followed by a delimiter
*/
/*
**	We initialize the heredoc
*/
t_read	*init_heredoc(t_data *data)
{
	t_read	*data_parsing;

	data_parsing = malloc(sizeof(t_read));
	data_parsing->c = 0;
	data_parsing->pos = 0;
	data_parsing->len = 0;
	data_parsing->current = NULL;
	data_parsing->str = NULL;
	data_parsing->data = data;
	return (data_parsing);
}

/*
**	We write until press enter,CTRL+C or exit
**	If the str doesnt match the redir word(delimiter)
**	The prompt comeback again
*/
void	write_heredoc(t_read *heredoc, t_redir *redir, int fd)
{
	while (ft_strncmp(redir->word, heredoc->str, \
	ft_strlen(redir->word) + 1))
	{
		heredoc->c = 0;
		heredoc->pos = 0;
		heredoc->len = 0;
		free_null((void **)&heredoc->str);
		ft_putstr_fd("> ", STDIN_FILENO);
		while (heredoc->c != NL_KEY)
		{
			heredoc->c = get_last_char(heredoc);
			if (heredoc->c == CTRL_C)
				stop_heredoc(heredoc);
			input_heredoc(heredoc, redir);
		}
		ft_putchar_fd('\n', STDIN_FILENO);
		if (!ft_strncmp(redir->word, heredoc->str, \
		ft_strlen(redir->word) + 1))
			break ;
		ft_putstr_fd(heredoc->str, fd);
		ft_putchar_fd('\n', fd);
	}
	free_null((void **)&heredoc->str);
}

/*
**	We create .heredoc and open it
**	We initialize the heredoc
**	We write on it,close it 
**	We open it agin for check if its still exist
**	If it is we unlink(destroy) it
*/
int	get_heredoc(t_data *data, t_redir *redir)
{
	int		fd;
	t_read	*heredoc;

	fd = open(".heredoc", O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (!fd)
		exit_custom(data, NULL, AUTO);
	heredoc = init_heredoc(data);
	write_heredoc(heredoc, redir, fd);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (!fd)
		exit_custom(data, NULL, AUTO);
	unlink(".heredoc");
	return (fd);
}
