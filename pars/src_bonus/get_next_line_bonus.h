/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:53:36 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 16:56:05 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "cub3d_bonus.h"

typedef struct s_node
{
	int				fd;
	char			*back_up;
	struct s_node	*next;
}	t_file_node;

typedef struct s_list
{
	t_file_node	*tail;
	t_file_node	*before;
	t_file_node	*current;
	size_t		total_fd;
}	t_list;

char	*get_next_line(int fd);
int		find_node(t_list *file_list, int fd);
int		add_node(t_list *file_list, int fd);
char	*read_file(t_list *file_list, char *buf);
char	*make_line(t_list *file_list);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
void	remove_list(t_list *file_list);

#endif