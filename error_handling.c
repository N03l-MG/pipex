/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:55:49 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/17 17:07:59 by nmonzon          ###   ########.fr       */
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
		ft_printf("pipex: %s: No such file or directory\n", pipex->infilename);
	else if (error_code == ERROR_OUTPUT)
		ft_printf("pipex: %s: No such file or directory\n", pipex->outfilename);
	free_pipe(pipex);
	exit(EXIT_SUCCESS);
}

void	error_handler(t_error error_code, t_pipe *pipex)
{
	if (error_code == ERROR_ARGS)
		ft_printf("Invalid arguments.\n");
	else if (error_code == ERROR_PIPE)
		ft_printf("Pipe error.\n");
	else if (error_code == ERROR_FORK)
		ft_printf("Fork error.\n");
	else if (error_code == ERROR_MEM)
		ft_printf("Memory allocation error.\n");
	free_pipe(pipex);
	exit(EXIT_FAILURE);
}

void	child_error_handler(t_error error_code, t_pipe *pipex)
{
	if (error_code == ERROR_CMD1)
		ft_printf("pipex: %s: command not found\n", pipex->cmd1[0]);
	else if (error_code == ERROR_CMD2)
		ft_printf("pipex: %s: command not found\n", pipex->cmd2[0]);
	exit(127);
}
