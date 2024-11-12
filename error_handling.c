/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:55:49 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/12 17:11:35 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipe(t_pipe *pipex)
{
	if (!pipex)
		return ;
	if (pipex->cmd1front)
		free(pipex->cmd1front);
	if (pipex->cmd2front)
		free(pipex->cmd2front);
	free(pipex);
}

void	error_handler(t_error error_code, t_pipe *pipex)
{
	if (error_code == ERROR_ARGS)
		ft_printf("Invalid arguments.\n");
	else if (error_code == ERROR_INPUT)
		ft_printf("zsh: no such file or directory: %s\n", pipex->infile);
	else if (error_code == ERROR_OUTPUT)
		ft_printf("zsh: no such file or directory: %s\n", pipex->outfile);
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
		ft_printf("zsh: command not found: %s\n", pipex->cmd1front);
	else if (error_code == ERROR_CMD2)
		ft_printf("zsh: command not found: %s\n", pipex->cmd2front);
	exit(EXIT_FAILURE);
}
