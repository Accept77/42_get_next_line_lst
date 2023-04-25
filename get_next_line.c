/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:48:07 by jinsyang          #+#    #+#             */
/*   Updated: 2023/04/25 18:35:13 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_and_null(t_top *stay, int *flag)
{
	t_list	*tmp;
	t_list	*next;

	*flag = 0;
	if (stay->next != NULL)
	{
		tmp = stay->next;
		while (tmp->next != NULL)
		{
			next = tmp->next;
			free(tmp->str);
			free(tmp);
			tmp = next;
		}
		free(tmp->str);
		free(tmp);
	}
	free(stay);
	stay = NULL;
}

void	fill_buf(char *buf, t_top *stay, int *fd_index, int fd)
{
	t_list	*tmp;
	t_list	*pre;
	int		index;

	index = 0;
	tmp = stay->next;
	while (tmp->next != NULL && tmp->fd != fd)
	{
		pre = tmp;
		tmp = tmp->next;
	}
	if (tmp->next == NULL && tmp->fd != fd) // 없으면 함수 종료
		return ;
	while (tmp->str[index] != '\0')
	{
		buf[index] = tmp->str[index];
		index++;
	}
	free(tmp->str);
	pre->next = tmp->next;
	free(tmp);
	*fd_index = index;
	return ;
}

void	fill_stay(t_top *stay, char *buf, int fd_index, int fd)
{
	t_list	*tmp;
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	new->fd = fd;
	new->str = gnl_strdup(buf, fd_index);
	new->next = NULL;
	if (stay->next != NULL)
	{
		tmp = stay->next;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (stay->next == NULL)
		stay->next = new;
}

char	*get_next_line2(char *result, int fd, int fd_index, int result_len)
{
	char			buf[BUFFER_SIZE];
	static t_top	*stay;
	int				index;
	int				flag;

	flag = 1;
	set_stay(stay);
	while (flag)
	{
		if (stay->next != NULL) // 여기
			fill_buf(buf, stay, &fd_index, fd); // 여기
		else
			fd_index = read(fd, buf, BUFFER_SIZE);
		if (fd_index < 0)
			free(result);
		if (fd_index <= 0)
			return (result);
		index = where_n(buf, fd_index, &flag);
		if (index != fd_index && BUFFER_SIZE != 1)
			fill_stay(stay, buf + index, fd_index - index, fd); // 여기
		result = result_is(result, &result_len, buf, index);
		if (!result)
			free_and_null(stay, &flag); // 여기
	}
	return (result);
}

char	*get_next_line(int fd)
{
	char	*result;
	int		result_len;
	int		fd_index;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	result = NULL;
	result_len = 0;
	fd_index = 0;
	result = get_next_line2(result, fd, fd_index, result_len);
	return (result);
}
