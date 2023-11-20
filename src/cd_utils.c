/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:53:10 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/20 13:02:17 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_oldpwd(t_envs *envs)
{
	free(envs->oldpwd);
	envs->oldpwd = ft_substr(envs->vars[pos_env_var(envs, "OLDPWD")],
			7, ft_strlen(envs->vars[pos_env_var(envs, "OLDPWD")]));
}

void	update_pwd(t_envs *envs)
{
	int	pwd_pos;
	int	oldpwd_pos;

	pwd_pos = pos_env_var(envs, "PWD");
	oldpwd_pos = pos_env_var(envs, "OLDPWD");
	if (envs->oldpwd)
		free(envs->oldpwd);
	envs->oldpwd = getcwd(envs->buf, PATH_MAX);
	free(envs->vars[oldpwd_pos]);
	free(envs->vars[pwd_pos]);
	envs->vars[pwd_pos] = ft_strjoin("PWD=", envs->oldpwd);
	envs->vars[oldpwd_pos] = ft_strjoin("OLDPWD=", envs->pwd);
}
