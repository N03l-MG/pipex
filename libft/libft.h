/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:48:54 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/17 17:40:27 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h> // malloc and free
# include <unistd.h> // read and write
# include <limits.h> // MIN_INT and other constants
# include <stdarg.h> // Variadic functions
# include <stdint.h> // Useful numeric types 
# include <fcntl.h> // File descriptor read flags
# include <stdbool.h> // Boolean type and true/false
# include <stdio.h> // For pipex project specifically

// Linked List Node
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Standard libft Functions
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_toupper(int c);

// ft_printf Implementation
int		ft_printf(const char *str, ...);

#endif
