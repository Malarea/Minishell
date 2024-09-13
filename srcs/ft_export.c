/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:42 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_env(t_data *data)
{
	char	**env;
	int		i;

	env = get_env(data);
	i = 0;
	while (env[i])
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	ft_free_arr(env);
}

void	modify_var(t_data *data, t_var *var, char *val)
{
	free_null((void **)&var->val);
	if (!val)
		var->val = NULL;
	else
	{
		var->val = ft_strdup(val);
		if (!var->val)
			exit_custom(data, NULL, AUTO);
	}
}

void	create_var(t_data *data, char *name, char *val)
{
	t_var	*new_var;

	new_var = malloc(sizeof(t_var));
	if (!new_var)
		exit_custom(data, NULL, AUTO);
	new_var->prev = NULL;
	new_var->next = NULL;
	new_var->name = ft_strdup(name);
	new_var->flag = ENV;
	if (!val)
		new_var->val = NULL;
	else
	{
		new_var->val = ft_strdup(val);
		if (!new_var->val)
			exit_custom(data, NULL, AUTO);
	}
	add_var_alpha(data, new_var);
}

void	export_var_def(t_data *data, char *arg)
{
	char	*name;
	char	*val;
	t_var	*current;
	int		i;

	name = NULL;
	val = NULL;
	current = data->var_lst;
	i = 0;
	while (arg[i] && arg[i] != '=')
		name = add_char(data, name, arg[i++]);
	if (arg[i] == '=')
		i++;
	while (arg[i])
		val = add_char(data, val, arg[i++]);
	while (current && ft_strncmp(name, current->name, ft_strlen(name) + 1))
		current = current->next;
	if (current)
		modify_var(data, current, val);
	else
		create_var(data, name, val);
	free_null((void **)&name);
	free_null((void **)&val);
}

int	ft_export(t_data *data, char **args)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	if (!args[1])
		export_env(data);
	if (args[1] && is_option(args[1]))
	{
		error_option(args[1], "export", &status);
		ft_free_arr(args);
		return (status);
	}
	while (args[i])
	{
		if (!data->cmd_lst->next && is_var_def(args[i]))
			export_var_def(data, args[i]);
		else if (!is_valid_var(args[i]) && !is_var_def(args[i]))
			error_identifier(args[i], "export", &status);
		i++;
	}
	ft_free_arr(args);
	return (status);
}
