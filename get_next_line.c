/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:48:07 by jinsyang          #+#    #+#             */
/*   Updated: 2023/02/06 14:32:37 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*result = NULL;
	char	buf[BUFFER_SIZE];
	static t_stay	*stay;
	int	fd_index = 0;
	int index = 1;
	int flag = 1;
	char	*tmp;
	int	result_len = 0;

	if (!stay)
		stay = (t_stay *)malloc(sizeof(t_stay));
	else if (stay->str)
	{
		while (stay->str[fd_index])
		{
			buf[fd_index] = stay->str[fd_index];
			fd_index++;
		}
		free(stay->str);
		stay->str = NULL;
//		gnl_del_cpy(&stay,fd,buf); // 여기
		flag = 2;
	}

	// result cpy = big size buff
	// buf cpy = read chaek
	while (flag)
	{
		if (flag != 2)
			fd_index = read(fd,buf,BUFFER_SIZE);
		flag = 1;
		if (fd_index < 0)
		{
			if (result)
				free(result);
			return (NULL);
		}
		else if (fd_index == 0)
			return (result);

		while (index < fd_index)
		{
			if (buf[index] == '\n')
			{
				index++;
				flag = 0;
				break;
			}
			index++;
		}

		result_len += index;

		if (result)
		{
			tmp = gnl_strdup(result, result_len);
			free(result);
			result = gnl_strjoin(tmp, buf, index, result_len);
			free(tmp);
			tmp = NULL;
		}
		else
			result = gnl_strdup(buf, index);
		if (!result)
			free(stay);
	}

	stay->str = gnl_strdup(buf + index, fd_index); // 여기가 문제임 fdindex 활용해야함
	stay->fd = fd;
	stay->next = NULL;
//gnl_lstadd_back(&stay, fd, buf, fd_index); // 여기

	return (result);
}
