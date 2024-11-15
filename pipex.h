/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:53:25 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/13 10:41:47 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_pipe
{
	int		infile;
	char	*infilename;
	int		outfile;
	char	*outfilename;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd1;
	char	*cmd1front;
	char	*cmd2;
	char	*cmd2front;
}	t_pipe;

typedef enum e_error
{
	ERROR_ARGS,
	ERROR_INPUT,
	ERROR_OUTPUT,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_CMD1,
	ERROR_CMD2,
	ERROR_MEM
}	t_error;

pid_t	child_process_one(t_pipe *pipex);
pid_t	child_process_two(t_pipe *pipex);
void	error_handler(t_error error_code, t_pipe *pipex);
void	child_error_handler(t_error error_code, t_pipe *pipex);
void	free_pipe(t_pipe *pipex);

#endif
