/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:48:07 by jinsyang          #+#    #+#             */
/*   Updated: 2023/02/08 19:21:00 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*result = NULL;
	static t_list	*head;
	char	buf[BUFFER_SIZE];
	int		result_len = 0;
	int			index;
	int			fd_index;
	int			flag = 1;
	char	*tmp;

	if (!head && BUFFER_SIZE != 1)
		head = (t_list *)malloc(sizeof(t_list));
	else if (head && head->next != NULL)
	{
		fd_index = cpy_buf(buf, fd, head); // !!!!!!!!!!!!!
		if (fd_index)
			flag = 2;
	}
	while (flag)
	{
		index = 0;
		if (flag != 2)
			fd_index = read(fd, buf, BUFFER_SIZE);
		if (fd_index == 0)
			return (result);
		else if (fd_index < 0)
		{
			free(result);
			return (NULL);
		}
		while (index < fd_index)
		{
			if (buf[index] == '\n')
			{
				flag = 0;
				index++;
				break ;
			}
			index++;
		}
		if (index != fd_index)
			new_node(head, buf + index, fd_index - index, fd);
		tmp = gnl_strdup(result, result_len);
		free(result);
		result = NULL;
		if (tmp == NULL)
			result = gnl_strdup(buf, index);
		else
			result = gnl_strjoin(tmp, buf, index, result_len);
		free(tmp);
		tmp = NULL;
		result_len += index;
		if (!result)
		{
			free_all(head);
			return (NULL);
		}
	}
	return (result);
}
