/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:49:12 by jinsyang          #+#    #+#             */
/*   Updated: 2023/01/31 17:49:34 by jinsyang         ###   ########.fr       */
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
	int 	i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(sizeof(char) * (result_len + index + 1));
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
	return (result);
}

void	gnl_lstfree(t_stay **stay)
{
	t_stay	*tmp;
	t_stay	*next;

	tmp = *stay;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = next;
	}
	free(stay);
	*stay = NULL;
}

void	gnl_lstadd_back(t_stay **stay, int fd, char *buf, int fd_index)
{
	t_stay	*tmp;
	t_stay	*new;
	new = (t_stay *)malloc(sizeof(t_stay));
	if (!new)
		return ;
	new->str = gnl_strdup(buf, fd_index);
	new->fd = fd;
	new->next = NULL;

	tmp = *stay;
	if (tmp)
		while (tmp->next != NULL)
			tmp = tmp->next;
	if (*stay == NULL)
	{
		new->next = *stay;
		*stay = new;
	}
	else
		tmp->next = new;
}

void	gnl_del_cpy(t_stay **stay, int fd, char *buf)
{
	t_stay *tmp;
	t_stay *pre;
	int i;

	tmp = *stay;
	pre = NULL;
	i = 0;
	if (tmp)
		while (tmp->fd != fd)
		{
			pre = tmp;
			tmp = tmp->next;
		}
	while (tmp->str)
	{
		buf[i] = tmp->str[i];
		i++;
	}
	pre->next = tmp->next;
	free(tmp->str);
	free(tmp);
}
