/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:53:25 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/17 14:03:06 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

// Pipe struct with all relevant variables
typedef struct s_pipe
{
	int		infile;
	char	*infilename;
	int		outfile;
	char	*outfilename;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1;
	char	**cmd2;
}	t_pipe;

// Error Types
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

// Parsing function for the environment path
char	*find_executable_path(char **cmd, char **envp);

// Both child process functions
pid_t	child_process_one(t_pipe *pipex, char **envp);
pid_t	child_process_two(t_pipe *pipex, char **envp);

// Error handling functions
void	error_success(t_error error_code, t_pipe *pipex);
void	error_handler(t_error error_code, t_pipe *pipex);
void	child_error_handler(t_error error_code, t_pipe *pipex);
void	free_pipe(t_pipe *pipex);
void	free_array(char **array);

#endif
