/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:20:35 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Syntax management,
**	We also skip quotes,check redirection error
**	And pipe error
*/
int	syntax_error(t_data *data, int flag)
{
	data->status = 2;
	if (flag == REDIR)
		ft_putstr_fd("minishell: redirection syntax error\n", STDERR_FILENO);
	else if (flag == PIPE)
		ft_putstr_fd("minishell: pipe syntax error\n", STDERR_FILENO);
	else
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	return (ERROR);
}

int	skip_quotes(char *str)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = str[i++];
	while (str[i] && str[i] != quote_type)
		i++;
	return (i);
}

int	check_redir_error(char *str)
{
	int	i;

	i = 1;
	if (str[i] == str[i - 1])
		i++;
	i += skip_ws(&str[i]);
	if (!str[i] || is_redir(str[i]) || str[i] == '|')
		return (1);
	return (0);
}

int	check_pipe_error(char *str)
{
	int	i;

	i = 1;
	i += skip_ws(&str[i]);
	if (!str[i] || str[i] == '|' || is_redir(str[i]))
		return (1);
	return (0);
}

int	check_syntax_error(t_data *data)
{
	int	i;

	i = 0;
	while (data->str[i])
	{
		if (check_quote(data->str, i))
			i += skip_quotes(&data->str[i]);
		else if (is_redir(data->str[i]) && check_redir_error(&data->str[i]))
			return (syntax_error(data, REDIR));
		else if (data->str[i] == '|' && check_pipe_error(&data->str[i]))
			return (syntax_error(data, PIPE));
		i++;
	}
	return (SUCCESS);
}
