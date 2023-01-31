/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:48:07 by jinsyang          #+#    #+#             */
/*   Updated: 2023/01/31 15:57:11 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*result = NULL;
	char	buf[BUFFER_SIZE];
	static t_stay	*stay;
	int	fd_index;
	int index = 1;
	int flag = 1;
	char	*tmp;
	int	result_len = 0;
	t_stay *stay_tmp;

	if (!stay)
		stay = (t_stay *)malloc(sizeof(t_stay));
	else if (stay)
	{
		stay_tmp = stay;

	}
		fd cheak reulst cpy stay del stay;

	while (flag)
	{
		fd_index = read(fd,buf,BUFFER_SIZE);
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

		tmp = gnl_strdup(result, result_len);
		free(result);
		if (!tmp)
			result = gnl_strdup(buf, index);
		else
			result = gnl_strjoin(tmp, buf, index, result_len);
		free(tmp);
		tmp = NULL;
	}

	!!lst save str fd;
	stay_tmp = stay;
	while (stay_tmp->next == NULL)
		stay_tmp = stay_tmp->next;
	stay->str = gnl_strdup(buf+index, fd_index);
	stay->fd = fd;
	if(!result)
		free(stay);

	return (result);
}
