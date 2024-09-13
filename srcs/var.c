/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:00:01 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(t_data *data, char *str, int *pos)
{
	char	*var_name;

	(*pos)++;
	var_name = NULL;
	if (str[*pos] == '?')
	{
		var_name = add_char(data, var_name, '?');
		(*pos)++;
	}
	else
	{
		while (str[*pos] && \
		(ft_isalnum(str[*pos]) || str[*pos] == '_') && \
		!ft_is_ws(str[*pos]))
		{
			var_name = add_char(data, var_name, str[*pos]);
			(*pos)++;
		}
	}
	return (var_name);
}

char	*get_var_val(t_data *data, char *var_name)
{
	t_var	*current;
	char	*var_val;

	current = data->var_lst;
	var_val = NULL;
	while (current)
	{
		if (!ft_strncmp(var_name, current->name, ft_strlen(var_name) + 1) && \
		current->val)
		{
			var_val = ft_strdup(current->val);
			if (!var_val)
				exit_custom(data, NULL, AUTO);
			return (var_val);
		}
		current = current->next;
	}
	return (var_val);
}

char	*get_var(t_data *data, char *str, int *pos)
{
	char	*var_name;
	char	*var_val;

	var_name = get_var_name(data, str, pos);
	if (!var_name)
	{
		var_val = malloc(2);
		if (!var_val)
			exit_custom(data, NULL, AUTO);
		var_val[0] = '$';
		var_val[1] = '\0';
	}
	else
		var_val = get_var_val(data, var_name);
	free_null((void **)&var_name);
	return (var_val);
}
