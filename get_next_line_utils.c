/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsyang <jinsyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:49:12 by jinsyang          #+#    #+#             */
/*   Updated: 2023/02/08 18:27:57 by jinsyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

void new_node(t_list *head, char *buf, int index, int fd)
{
	t_list *new;
	t_list *tmp;

	new = (t_list *)malloc(sizeof(t_list));
	tmp = head;
	if (!new)
		return ;
	new->str = gnl_strdup(buf, index);
	if (!new->str)
	{
		free(new);
		return ;
	}
	new->fd = fd;
	new->next = NULL;

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void free_all(t_list *head)
{
	t_list *tmp;
	t_list *next;

	tmp = head;
	while (tmp->next != NULL)
	{
		next = next->next;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
		tmp = next;
	}
	free(head);
	head = NULL;
}

int cpy_buf(char *buf, int fd, t_list *head)
{
	t_list *pre;
	int	index;

	index = 0;
	while (head->fd != fd && head->next != NULL)
	{
		pre = head;
		head = head->next;
	}
	if (head->fd != fd && head->next == NULL)
		return 0;
	pre->next = head->next;

	while (head->str[index])
	{
		buf[index] = head->str[index];
		index++;
	}
	free(head->str);
	head->str = NULL;
	free(head);
	head = NULL;
	return(index);
}
