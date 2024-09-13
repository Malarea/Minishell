/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:44:42 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Set redirections < or >
*/
void	set_redir(t_data *data, int *pos, t_cmd *cmd)
{
	if (data->str[*pos] == '<')
		set_redir_in(data, pos, cmd);
	else
		set_redir_out(data, pos, cmd);
}

/*
**	Set args,parameters $ or quotes
*/
void	set_args(t_data *data, int *pos, t_cmd *cmd)
{
	int		quote_type;

	while (data->str[*pos] && !is_redir(data->str[*pos]) && \
	data->str[*pos] != '|')
	{
		if (data->str[*pos] == '$')
			cmd->args = concat_str(data, cmd->args, \
			get_var(data, data->str, pos));
		else if (check_quote(data->str, *pos))
		{
			quote_type = data->str[*pos];
			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
			while (data->str[*pos] && data->str[*pos] != quote_type)
				cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
			if (data->str[*pos] == quote_type)
				cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
		}
		else
			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
	}
}
