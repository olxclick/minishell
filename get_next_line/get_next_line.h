/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:25:33 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/10 22:17:42 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*get_next_line(int fd);
// char	*ft_strchr(const char *s, int c);
char	*read_file(int fd, char *backup);
char	*get_myline(char *res);
char	*remove_read(char *backup);

#endif
