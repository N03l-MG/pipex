/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:50:01 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/12 17:11:39 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		create_pipe(int infile, int outfile, int *pipefd);
static pid_t	child_process_one(int in, int *pipefd, char *cmd);
static pid_t	child_process_two(int out, int *pipefd, char *cmd);

int	main(int argc, char *argv[])
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (EXIT_FAILURE);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	create_pipe(infile, outfile, pipefd);
	pid1 = child_process_one(infile, pipefd, argv[2]);
	pid2 = child_process_two(outfile, pipefd, argv[3]);
	close(infile);
	close(outfile);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}

static void	create_pipe(int infile, int outfile, int *pipefd)
{
	if (infile < 0)
		error_handler(ERROR_INPUT, EXIT_FAILURE);

	if (outfile < 0)
	{
		close(infile);
		error_handler(ERROR_OUTPUT, EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		close(infile);
		close(outfile);
		error_handler(ERROR_PIPE, EXIT_FAILURE);
	}
}

static pid_t	child_process_one(int in, int *pipefd, char *cmd)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		close(in);
		error_handler(ERROR_FORK, EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(in, STDOUT_FILENO);
		close(in);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("/bin/sh", "sh", "-c", cmd, (char *) NULL);
		perror("execlp cmd1");
		exit(EXIT_FAILURE);
	}
	return (pid2);
}

static pid_t	child_process_two(int out, int *pipefd, char *cmd)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		close(out);
		error_handler(ERROR_FORK, EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close(out);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("/bin/sh", "sh", "-c", cmd, (char *) NULL);
		perror("execlp cmd2");
		exit(EXIT_FAILURE);
	}
	return (pid2);
}
