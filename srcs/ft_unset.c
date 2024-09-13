/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:21:02 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We unset the var and check if there is an option if it is it's return an error
*/
void	unset_var(t_data *data, char *arg)
{
	t_var	*current;

	current = data->var_lst;
	while (current)
	{
		if (!ft_strncmp(current->name, arg, ft_strlen(current->name) + 1))
		{
			if (current->next)
				current->next->prev = current->prev;
			if (current->prev)
				current->prev->next = current->next;
			free_null((void **)&current->name);
			free_null((void **)&current->val);
			free_null((void **)&current);
			return ;
		}
		current = current->next;
	}
}

int	ft_unset(t_data *data, char **args)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	if (args[1] && is_option(args[1]))
	{
		error_option(args[1], "unset", &status);
		ft_free_arr(args);
		return (status);
	}
	while (args[i])
	{
		if (!data->cmd_lst->next && is_valid_var(args[i]))
			unset_var(data, args[i]);
		else if (!is_valid_var(args[i]))
			error_identifier(args[i], "unset", &status);
		i++;
	}
	ft_free_arr(args);
	return (status);
}
