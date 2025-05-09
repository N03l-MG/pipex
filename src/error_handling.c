/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:55:49 by kixik             #+#    #+#             */
/*   Updated: 2024/11/25 17:13:39 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
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

void	free_pipe(t_pipe *pipex)
{
	if (!pipex)
		return ;
	if (pipex->cmd1)
		free_array(pipex->cmd1);
	if (pipex->cmd2)
		free_array(pipex->cmd2);
	free(pipex);
}

void	error_success(t_error error_code, t_pipe *pipex)
{
	if (error_code == ERROR_INPUT)
		ft_fprintf(2, "sh: %s: No such file or directory\n", pipex->infilename);
	else if (error_code == ERROR_OUTPUT)
		ft_fprintf(2, "sh: %s: No such file or directory\n", pipex->outfilename);
	free_pipe(pipex);
	exit(EXIT_SUCCESS);
}

void	error_handler(t_error error_code, t_pipe *pipex)
{
	if (error_code == ERROR_ARGS)
		ft_fprintf(2, "Invalid arguments.\n");
	else if (error_code == ERROR_PIPE)
		ft_fprintf(2, "Pipe error.\n");
	else if (error_code == ERROR_FORK)
		ft_fprintf(2, "Fork error.\n");
	else if (error_code == ERROR_MEM)
		ft_fprintf(2, "Memory allocation error.\n");
	free_pipe(pipex);
	exit(EXIT_FAILURE);
}

void	child_error_handler(t_error error_code, t_pipe *pipex)
{
	if (error_code == ERROR_CMD1)
		ft_fprintf(2, "sh: %s: command not found\n", pipex->cmd1[0]);
	else if (error_code == ERROR_CMD2)
		ft_fprintf(2, "sh: %s: command not found\n", pipex->cmd2[0]);
	exit(127);
}
