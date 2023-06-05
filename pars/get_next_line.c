/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:38:05 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/29 15:36:46 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	file_list;
	char			*buf;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (find_node(&file_list, fd) == -1)
		if (add_node(&file_list, fd) == -1)
			return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
	{
		remove_list(&file_list);
		return (NULL);
	}
	if (read_file(&file_list, buf) == NULL)
	{
		free(buf);
		remove_list(&file_list);
		return (NULL);
	}
	line = make_line(&file_list);
	return (line);
}

int	find_node(t_list *file_list, int fd)
{
	size_t	i;

	i = 0;
	if (file_list->tail == NULL)
		return (-1);
	while (i < file_list->total_fd)
	{
		if (file_list->current->fd == fd)
			return (file_list->current->fd);
		file_list->before = file_list->current;
		file_list->current = file_list->current->next;
		i++;
	}
	return (-1);
}

int	add_node(t_list *file_list, int fd)
{
	t_file_node	*file_node;

	file_node = (t_file_node *)malloc(sizeof(t_file_node));
	if (file_node == NULL)
		return (-1);
	file_node->back_up = (char *)malloc(1);
	if (file_node->back_up == NULL)
	{
		free(file_node);
		return (-1);
	}
	if (file_list->tail == NULL)
	{
		file_list->tail = file_node;
		file_node->next = file_node;
	}
	file_node->back_up[0] = '\0';
	file_node->fd = fd;
	file_node->next = file_list->tail->next;
	file_list->tail->next = file_node;
	file_list->before = file_list->tail;
	file_list->tail = file_node;
	file_list->current = file_node;
	file_list->total_fd++;
	return (0);
}

char	*read_file(t_list *file_list, char *buf)
{
	ssize_t	nbyte;
	char	*back_up_free;

	while (1)
	{
		if ((ft_strchr(file_list->current->back_up, '\n')))
			break ;
		nbyte = read(file_list->current->fd, buf, BUFFER_SIZE);
		if (nbyte == 0)
			break ;
		if (nbyte < 0)
			return (NULL);
		buf[nbyte] = '\0';
		back_up_free = file_list->current->back_up;
		file_list->current->back_up = \
		ft_strjoin(file_list->current->back_up, buf);
		free(back_up_free);
		if (file_list->current->back_up == NULL)
			return (NULL);
	}
	if (file_list->current->back_up[0] == '\0')
		return (NULL);
	free(buf);
	return (file_list->current->back_up);
}

char	*make_line(t_list *file_list)
{
	int		i;
	char	*line;
	char	*back_up;
	char	*tmp;

	i = 0;
	back_up = file_list->current->back_up;
	while (back_up[i] != '\n' && back_up[i] != '\0')
		i++;
	line = ft_substr(back_up, 0, i + 1);
	if (line == NULL || back_up[i] != '\n')
	{
		remove_list(file_list);
		return (line);
	}
	tmp = ft_substr(back_up, i + 1, ft_strlen(back_up) - i - 1);
	if (tmp == NULL)
	{
		free(line);
		remove_list(file_list);
		return (NULL);
	}
	free(file_list->current->back_up);
	file_list->current->back_up = tmp;
	return (line);
}
