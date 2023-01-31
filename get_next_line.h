/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:49:22 by jinsyang          #+#    #+#             */
/*   Updated: 2023/01/31 17:49:04 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_stay {
	char *str;
	int	fd;
	struct s_stay *next;
}	t_stay;

char	*get_next_line(int fd);
char	*gnl_strdup(char *s1, int index);
char	*gnl_strjoin(char *tmp, char *buf, int index, int result_len);
void	gnl_del_cpy(t_stay **stay, int fd, char *buf);
void	gnl_lstadd_back(t_stay **stay, int fd, char *buf, int fd_index);
void	gnl_lstfree(t_stay **stay);
#endif
