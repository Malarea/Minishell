/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:25:42 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_def(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (ft_isalnum(arg[i]) || arg[i] == '_' || arg[i] == '=')
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_var(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_var	*skip_status_var(t_data *data)
{
	t_var	*current;

	current = data->var_lst;
	if (current->flag == SPECIAL && current->next)
		current = current->next;
	return (current);
}

void	add_var_alpha(t_data *data, t_var *var)
{
	t_var	*current;
	t_var	*tmp;
	int		i;

	current = skip_status_var(data);
	while (current->next)
	{
		i = 0;
		while (current->name[i] && var->name[i] && \
		current->name[i] == var->name[i])
			i++;
		if (current->name[i] > var->name[i])
		{
			tmp = current->prev;
			current->prev = var;
			tmp->next = var;
			var->prev = tmp;
			var->next = current;
			return ;
		}
		current = current->next;
	}
	var->prev = current;
	current->next = var;
}

void	error_identifier(char *arg, char *cmd, int *status)
{
	ft_putstr_fd("minishell: '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	*status = 1;
}
