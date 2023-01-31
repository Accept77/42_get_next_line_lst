/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:48:07 by jinsyang          #+#    #+#             */
/*   Updated: 2023/01/31 17:49:36 by jinsyang         ###   ########.fr       */
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

	if (!stay)
		stay = (t_stay *)malloc(sizeof(t_stay));
	else if (stay)
	{
		gnl_del_cpy(&stay,fd,buf);
		flag = 2;
	}
//		fd cheak reulst cpy stay del stay;
//		buf? result?;
//		result = BUFFER_SIZE big think;
//		buf = cheak buf cpy flag?;
//
//	result read해서 한번에 저장한다음 n찾고 나머지 stay저장하기;
//	아니면 buf에다가 stay 복사 해서 buf에서 n찾기;
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

		tmp = gnl_strdup(result, result_len);
		free(result);
		if (!tmp)
			result = gnl_strdup(buf, index);
		else
			result = gnl_strjoin(tmp, buf, index, result_len);
		free(tmp);
		tmp = NULL;
	}

//	!!lst save str fd;

	gnl_lstadd_back(&stay, fd, buf, fd_index);
	if(!result)
		gnl_lstfree(&stay);

	return (result);
}
