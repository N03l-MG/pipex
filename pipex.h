/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:53:25 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/12 17:11:34 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_pipeparams
{
	char	*input;
	char	*output;
	pid_t	process1;
	pid_t	process2;
}	t_pipeparams;

typedef enum e_error
{
	ERROR_INPUT,
	ERROR_OUTPUT,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_CMD1,
	ERROR_CMD2,
	ERROR_MEM
}	t_error;

void	error_handler(t_error error_code, t_pipeparams);

#endif
