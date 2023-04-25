/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:49:22 by jinsyang          #+#    #+#             */
/*   Updated: 2023/04/25 15:56:23 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list {
	char			*str;
	int				fd;
	struct s_list	*next;
}	t_list;

typedef struct s_top {
	t_list	*next;
}	t_top;

char	*get_next_line(int fd);
char	*gnl_strdup(char *s1, int index);
char	*gnl_strjoin(char *tmp, char *buf, int index, int result_len);
char	*result_is(char *result, int *result_len, char *buf, int index);
int		where_n(char *buf, int fd_index, int *flag);
void	set_stay(t_top *stay);

#endif
