/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:44:34 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/15 16:20:37 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_string(char *str, int *retval)
{
	if (!str)
	{
		if (write(2, "(null)", 6) == -1)
		{
			*retval = -1;
			return ;
		}
		(*retval) += 6;
		return ;
	}
	while (*str)
	{
		if (write(2, str, 1) == -1)
		{
			*retval = -1;
			return ;
		}
		str++;
		(*retval)++;
	}
}
