/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We store the new cmd in t_cmd struct
*/
t_cmd	*new_elem_cmd(t_data *data)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		exit_custom(data, NULL, AUTO);
	elem->in_lst = NULL;
	elem->out_lst = NULL;
	elem->args = NULL;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

/*
**	We add cmd to cmd_lst
*/
void	add_cmd_lst(t_cmd **cmd_lst, t_cmd *cmd)
{
	t_cmd	*current;

	if (!(*cmd_lst))
	{
		*cmd_lst = cmd;
		return ;
	}
	current = *cmd_lst;
	while (current->next)
		current = current->next;
	current->next = cmd;
	cmd->prev = current;
}

/*
**	We free cmd_lst
*/
void	free_cmd_lst(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = data->cmd_lst;
	if (!cmd)
		return ;
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		next = cmd->next;
		free_redir_lst(cmd->in_lst);
		cmd->in_lst = NULL;
		free_redir_lst(cmd->out_lst);
		cmd->out_lst = NULL;
		free_null((void **)&(cmd->args));
		free_null((void **)&cmd);
		cmd = next;
	}
	data->cmd_lst = NULL;
}

/*
**	After add cmd to cmd_lst
**	We check if cmd contains whitespace
**	We check if cmd contains redir or arg(params)
**	When we encounter a pipe the while restart for the next cmd
*/
t_cmd	*get_cmd_lst(t_data *data)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	cmd_lst = NULL;
	i = 0;
	while (data->str[i])
	{
		cmd = new_elem_cmd(data);
		add_cmd_lst(&cmd_lst, cmd);
		while (data->str[i] && data->str[i] != '|')
		{
			i += skip_ws(&data->str[i]);
			if (is_redir(data->str[i]))
				set_redir(data, &i, cmd);
			else
				set_args(data, &i, cmd);
		}
		if (data->str[i] == '|')
			i++;
	}
	return (cmd_lst);
}
