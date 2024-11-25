/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:05:51 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 17:12:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	ft_fprintf(2, "Error: PATH environment variable not found.\n");
	exit(EXIT_FAILURE);
}

static void	build_path(char *full_path, const char *path, const char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i] != '\0')
	{
		full_path[i] = path[i];
		i++;
	}
	full_path[i] = '/';
	i++;
	while (cmd[j] != '\0')
	{
		full_path[i] = cmd[j];
		i++;
		j++;
	}
	full_path[i] = '\0';
}

char	*find_executable_path(char **cmd, char **envp)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path_var = get_env_path(envp);
	paths = ft_split(path_var, ':');
	if (!paths)
		error_handler(ERROR_MEM, NULL);
	while (paths[i])
	{
		full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd[0]) + 2);
		if (!full_path)
			error_handler(ERROR_MEM, NULL);
		build_path(full_path, paths[i++], cmd[0]);
		if (access(full_path, X_OK | F_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_array(paths);
	return (NULL);
}
