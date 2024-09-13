/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:27:42 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_var_lst(t_var *var_lst)
{
	t_var	*current;
	t_var	*next;

	current = var_lst;
	while (current)
	{
		next = current->next;
		free_null((void **)&current->name);
		free_null((void **)&current->val);
		free_null((void **)&current);
		current = next;
	}
}

void	free_data(t_data *data)
{
	free_var_lst(data->var_lst);
	free_cmd_lst(data);
	free_null((void **)&(data->str));
	free_null((void **)&data);
}

char	*custom_strerror(int status, char *word)
{
	if (status == 0)
		return ("Success\n");
	else if (status == 1)
		return ("No such file or directory\n");
	else if (status == 127)
	{
		if (check_slash_in(word))
			return ("No such file or directory\n");
		return ("command not found\n");
	}
	return (NULL);
}

void	exit_custom(t_data *data, char *word, int flag)
{
	int	status;

	status = data->status;
	free_history(data->history);
	free_data(data);
	if (flag == CUSTOM)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (word)
		{
			ft_putstr_fd(word, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(custom_strerror(status, word), STDERR_FILENO);
		free_null((void **)&word);
		exit(status);
	}
	exit_strerror();
}

void	close_fd(void)
{
	int	i;

	i = 0;
	while (i < 256)
		close (i++);
}
