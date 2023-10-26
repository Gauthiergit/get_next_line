/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:04:18 by gpeyre            #+#    #+#             */
/*   Updated: 2023/10/26 16:37:27 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clean_line(char **str)
{
	char	*line;
	char	*temp;
	int		len;

	len = 0;
	temp = *str;
	while (temp[len] && temp[len] != '\n')
		len++;
	if (temp[len] == '\n')
	{
		line = ft_substr(temp, 0, len + 1);
		*str = ft_substr(temp, (len + 1), ft_strlen(temp) - (len + 1));
		free(temp);
		if (!**str)
		{
			free(*str);
			*str = NULL;
		}
		return (line);
	}
	line = ft_substr(*str, 0, len);
	free(*str);
	*str = NULL;
	return (line);
}

static int	read_fd(int fd, char **stash)
{
	char	*buff;
	int		nb_read;
	char	*temp;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (-1);
	nb_read = read(fd, buff, BUFFER_SIZE);
	while (nb_read > 0)
	{
		buff[nb_read] = '\0';
		if (!(*stash))
			*stash = ft_strdup("");
		temp = *stash;
		*stash = ft_strjoin(temp, buff);
		free(temp);
		if (ft_strchr(*stash, '\n'))
			break ;
		nb_read = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (nb_read);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	int			nb_read;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > MAX_FD)
		return (NULL);
	nb_read = read_fd(fd, &stash[fd]);
	if (nb_read == -1)
		return (NULL);
	if (!nb_read && !stash[fd])
		return (NULL);
	line = clean_line(&stash[fd]);
	return (line);
}
/* #include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char *next_line;
	int	fd1 = open("mydict.txt", O_RDONLY);
	int	fd2 = open("mydict.txt", O_RDONLY);
	int	fd3 = open("mydict.txt", O_RDONLY);
	int	fd4 = open("mydict.txt", O_RDONLY);

	next_line = get_next_line(fd1);
	printf("[%s]\n", next_line);
	free(next_line);
	next_line = get_next_line(fd2);
	printf("[%s]\n", next_line);
	free(next_line);
	next_line = get_next_line(fd1);
	printf("[%s]\n", next_line);
	free(next_line);
	next_line = get_next_line(fd3);
	printf("[%s]\n", next_line);
	free(next_line);
	next_line = get_next_line(fd1);
	printf("[%s]\n", next_line);
	free(next_line);
	next_line = get_next_line(fd1);
	printf("[%s]\n", next_line);
	free(next_line);
	next_line = get_next_line(fd4);
	printf("[%s]\n", next_line);
	free(next_line);
	next_line = get_next_line(fd3);
	printf("[%s]\n", next_line);
	free(next_line);

	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
} */