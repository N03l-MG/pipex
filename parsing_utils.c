/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:05:51 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/16 15:29:31 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_array(char **array);

char	*find_executable_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
	if (!path_env)
		error_handler(ERROR_MEM, NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		error_handler(ERROR_MEM, NULL);
	i = 0;
	while (paths[i])
	{
		full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
		{
			free_array(paths);
			error_handler(ERROR_MEM, NULL);
		}
		ft_strlcpy(full_path, paths[i], ft_strlen(full_path));
		ft_strlcat(full_path, "/", ft_strlen(full_path));
		ft_strlcat(full_path, cmd, ft_strlen(full_path));
		if (access(full_path, X_OK | F_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}
