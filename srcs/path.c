/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:42:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/07 09:43:35 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_from_env(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	path = ft_split(env[i] + 5, ':');
	return (path);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*dest;
	char	**path;
	char	*tmp;

	i = 0;
	path = get_path_from_env(env);
	tmp = ft_strjoin("/", cmd);
	while (path && path[i])
	{
		dest = ft_strjoin(path[i], tmp);
		if (access(dest, F_OK | X_OK) == 0)
		{
			free(tmp);
			ft_free_tab(path);
			return (dest);
		}
		free(dest);
		i++;
	}
	ft_free_tab(path);
	free(tmp);
	return (NULL);
}
