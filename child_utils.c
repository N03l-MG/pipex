/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:20:12 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/16 15:30:28 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	child_process_one(t_pipe *pipex)
{
	pid_t	pid1;
	char	*cmd1_path;

	pid1 = fork();
	if (pid1 == -1)
	{
		close(pipex->infile);
		error_handler(ERROR_FORK, pipex);
	}
	if (pid1 == 0)
	{
		cmd1_path = find_executable_path(pipex->cmd1);
		if (!cmd1_path)
			child_error_handler(ERROR_CMD1, pipex);
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->infile);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		execv(cmd1_path, &pipex->cmd1);
		free(cmd1_path);
		child_error_handler(ERROR_CMD1, pipex);
	}
	return (pid1);
}

pid_t	child_process_two(t_pipe *pipex)
{
	pid_t	pid2;
	char	*cmd2_path;

	pid2 = fork();
	if (pid2 == -1)
	{
		close(pipex->outfile);
		error_handler(ERROR_FORK, pipex);
	}
	if (pid2 == 0)
	{
		cmd2_path = find_executable_path(pipex->cmd2);
		if (!cmd2_path)
			child_error_handler(ERROR_CMD1, pipex);
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		execv(cmd2_path, &pipex->cmd2);
		free(cmd2_path);
		child_error_handler(ERROR_CMD1, pipex);
	}
	return (pid2);
}
