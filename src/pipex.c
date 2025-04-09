/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:50:01 by kixik             #+#    #+#             */
/*   Updated: 2024/11/17 17:43:27 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		parse_args(char **args, t_pipe *pipex);
static void		create_pipe(t_pipe *pipex);
static void		close_all(t_pipe *pipex);

int	main(int argc, char *argv[], char **envp)
{
	t_pipe	*pipex;
	int		status;

	status = 0;
	if (argc != 5)
		error_handler(ERROR_ARGS, NULL);
	pipex = (t_pipe *)malloc(sizeof(t_pipe));
	parse_args(argv + 1, pipex);
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	create_pipe(pipex);
	pipex->pid1 = child_process_one(pipex, envp);
	pipex->pid2 = child_process_two(pipex, envp);
	close_all(pipex);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &status, 0);
	free_pipe(pipex);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static void	parse_args(char **args, t_pipe *pipex)
{
	pipex->infilename = args[0];
	pipex->outfilename = args[3];
	pipex->cmd1 = ft_split(args[1], ' ');
	pipex->cmd2 = ft_split(args[2], ' ');
}

static void	create_pipe(t_pipe *pipex)
{
	if (pipex->infile < 0)
		error_success(ERROR_INPUT, pipex);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		error_success(ERROR_OUTPUT, pipex);
	}
	if (pipe(pipex->pipefd) == -1)
	{
		close(pipex->infile);
		close(pipex->outfile);
		error_handler(ERROR_PIPE, pipex);
	}
}

static void	close_all(t_pipe *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}
