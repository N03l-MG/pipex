/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:50:01 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/15 16:28:40 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		parse_args(char **args, t_pipe *pipex);
static char		*make_cmdstr(char *cmd);
static void		create_pipe(t_pipe *pipex);

int	main(int argc, char *argv[])
{
	t_pipe	*pipex;

	pipex = (t_pipe *)malloc(sizeof(t_pipe));
	if (argc != 5)
		error_handler(ERROR_ARGS, NULL);
	parse_args(argv + 1, pipex);
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	create_pipe(pipex);
	pipex->pid1 = child_process_one(pipex);
	pipex->pid2 = child_process_two(pipex);
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	free_pipe(pipex);
	return (EXIT_SUCCESS);
}

static void	parse_args(char **args, t_pipe *pipex)
{
	pipex->infilename = args[0];
	pipex->outfilename = args[3];
	pipex->cmd1 = args[1];
	pipex->cmd2 = args[2];
	pipex->cmd1front = make_cmdstr(args[1]);
	pipex->cmd2front = make_cmdstr(args[2]);
}

static char	*make_cmdstr(char *cmd)
{
	int		i;
	char	*cmdstr;

	i = 0;
	while (cmd[i] != ' ' && cmd[i] != '\n')
		i++;
	cmdstr = (char *)malloc(i + 1);
	if (!cmdstr)
		error_handler(ERROR_MEM, NULL);
	i = 0;
	while (cmd[i] != ' ' && cmd[i] != '\n')
	{
		cmdstr[i] = cmd[i];
		i++;
	}
	cmdstr[i] = '\0';
	return (cmdstr);
}

static void	create_pipe(t_pipe *pipex)
{
	if (pipex->infile < 0)
		error_handler(ERROR_INPUT, pipex);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		error_handler(ERROR_OUTPUT, pipex);
	}
	if (pipe(pipex->pipefd) == -1)
	{
		close(pipex->infile);
		close(pipex->outfile);
		error_handler(ERROR_PIPE, pipex);
	}
}
