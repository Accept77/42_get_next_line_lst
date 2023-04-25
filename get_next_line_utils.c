/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:49:12 by jinsyang          #+#    #+#             */
/*   Updated: 2023/04/25 15:55:59 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *s1, int index)
{
	char	*result;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	result = (char *) malloc(sizeof(char) * index + 1);
	if (!result)
		return (NULL);
	if (index == 0)
	{
		result[0] = '\0';
		return (result);
	}
	while (i < index && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*gnl_strjoin(char *tmp, char *buf, int index, int result_len)
{
	char	*result;
	int		i;
	int		j;

	result = (char *)malloc(sizeof(char) * (result_len + index + 1));
	i = 0;
	j = 0;
	if (!result)
		return (NULL);
	while (i < result_len)
	{
		result[j] = tmp[i];
		i++;
		j++;
	}
	i = 0;
	while (i < index)
	{
		result[j] = buf[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*result_is(char *result, int *result_len, char *buf, int index)
{
	char	*tmp;

	tmp = gnl_strdup(result, *result_len);
	free(result);
	result = NULL;
	if (tmp == NULL)
		result = gnl_strdup(buf, index);
	else
		result = gnl_strjoin(tmp, buf, index, *result_len);
	free(tmp);
	tmp = NULL;
	*result_len += index;
	return (result);
}

int	where_n(char *buf, int fd_index, int *flag)
{
	int	index;

	index = 0;
	while (index < fd_index)
	{
		if (buf[index] == '\n')
		{
			*flag = 0;
			index++;
			break ;
		}
		index++;
	}
	return (index);
}

void	set_stay(t_top *stay)
{
	stay = (t_top *)malloc(sizeof(t_top));
	stay->next = NULL;
}
