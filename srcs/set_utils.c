/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:24:52 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_flag_in(t_data *data, int *pos)
{
	(*pos)++;
	if (data->str[*pos] == '<')
	{
		(*pos)++;
		return (DOUBLE_LEFT);
	}
	return (SIMPLE_LEFT);
}

int	get_flag_out(t_data *data, int *pos)
{
	(*pos)++;
	if (data->str[*pos] == '>')
	{
		(*pos)++;
		return (DOUBLE_RIGHT);
	}
	return (SIMPLE_RIGHT);
}

void	set_redir_in(t_data *data, int *pos, t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*redir;

	current = cmd->in_lst;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit_custom(data, NULL, AUTO);
	redir->prev = NULL;
	redir->next = NULL;
	redir->flag = get_flag_in(data, pos);
	if (redir->flag == DOUBLE_LEFT)
		redir->word = get_word(data, pos);
	else
		redir->word = get_file_word(data, pos);
	if (!cmd->in_lst)
		cmd->in_lst = redir;
	else
	{
		while (current->next)
			current = current->next;
		redir->prev = current;
		current->next = redir;
	}
}

void	set_redir_out(t_data *data, int *pos, t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*redir;

	current = cmd->out_lst;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit_custom(data, NULL, AUTO);
	redir->prev = NULL;
	redir->next = NULL;
	redir->flag = get_flag_out(data, pos);
	redir->word = get_file_word(data, pos);
	if (!cmd->out_lst)
		cmd->out_lst = redir;
	else
	{
		while (current->next)
			current = current->next;
		redir->prev = current;
		current->next = redir;
	}
}
