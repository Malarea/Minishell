/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:22:40 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We edit the env var PWD and OLDPWD,
**	We put the new pwd to PWD and the old pwd to OLDPWD
*/
void	edit_env_value(t_var *env, char *new_pwd, char *ex_pwd)
{
	t_var	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->name, 4) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup(new_pwd);
		}
		if (ft_strncmp("OLDPWD", tmp->name, 7) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup(ex_pwd);
		}
		tmp = tmp->next;
	}
}

/*
**	We check errors(options,args)
**	We check others errors (path,can't get cwd,var exist)
**	If its ok we edit the PWD and OLDPWD var
*/
int	ft_cd(t_data *data, char **path)
{
	char	new_pwd[PATH_MAX_B];
	char	ex_pwd[PATH_MAX_B];
	int		status;

	status = 0;
	if (path[1] && is_option(path[1]))
		error_option(path[1], "cd", &status);
	else if (path[1] && path[2])
		error_cd_args(&status);
	else if (path[1] && check_stat_path(path[1]))
	{
		if (!data->cmd_lst->next && !getcwd(ex_pwd, PATH_MAX_B))
			error_cwd(&status);
		if (!data->cmd_lst->next && chdir(path[1]) == ERROR)
			error_path(path[1], &status);
		if (!data->cmd_lst->next && !getcwd(new_pwd, PATH_MAX_B))
			error_cwd(&status);
		edit_env_value(data->var_lst, new_pwd, ex_pwd);
	}
	else if (path[1] && !check_stat_path(path[1]))
		error_path(path[1], &status);
	ft_free_arr(path);
	return (status);
}
