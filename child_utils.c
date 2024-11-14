/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:20:12 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/13 10:26:01 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	child_process_one(t_pipe *pipex)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		close(pipex->infile);
		error_handler(ERROR_FORK, pipex);
	}
	if (pid1 == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->infile);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		execlp("/bin/sh", "sh", "-c", pipex->cmd1, (char *) NULL);
		child_error_handler(ERROR_CMD1, pipex);
	}
	return (pid1);
}

pid_t	child_process_two(t_pipe *pipex)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		close(pipex->outfile);
		error_handler(ERROR_FORK, pipex);
	}
	if (pid2 == 0)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		execlp("/bin/sh", "sh", "-c", pipex->cmd2, (char *) NULL);
		child_error_handler(ERROR_CMD1, pipex);
	}
	return (pid2);
}
