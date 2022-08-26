/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:00:00 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/15 18:00:00 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 ** @brief      Extract the first line from the string pointed to by temp and
 **             shift temp address to the beginning of the next line or NULL if
 **             the end of the string is reached.
 **
 ** @param[in]  temp a static pointer to the first line.
 ** @param[out] temp a static pointer to the next line: temp + ft_strlen(line)
 ** @return     The first line that temp was pointing to or NULL.
 */

static char	*ft_next(char **temp)
{
	char	*line;
	char	*ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		++ptr;
	ptr += (*ptr == '\n');
	line = ft_substr (*temp, 0, (size_t)(ptr - *temp));
	if (!line)
		return (free (*temp), NULL);
	ptr = ft_substr (ptr, 0, ft_strlen (ptr));
	free (*temp);
	*temp = ptr;
	return (line);
}

/*
 ** @brief      Read the content of the file pointed to by fd.
 **
 ** @param[in]  fd a file descriptor pointing to a file.
 ** @param[in]  temp a static pointer to the content read.
 ** @return     A pointer to:
 **             - a line, if BUFFER_SIZE is smaller than a line.
 **             - a line + more, if BUFFER_SIZE is bigger than a line
 **               or if it is not the first get_next_line call for this fd.
 **             - NULL if there is nothing left to be read on fd.
 */

static char	*ft_read(char *temp, int fd)
{
	char		*buf;
	ssize_t		r;

	buf = malloc (sizeof (*buf) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free (temp);
		return (NULL);
	}
	r = 1;
	while (r && !ft_strchr (temp, '\n'))
	{
		r = read (fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (free (buf), free (temp), NULL);
		buf[r] = 0;
		temp = ft_strjoin_free_s1 (temp, buf);
		if (!temp)
			return (free (buf), NULL);
	}
	free (buf);
	return (temp);
}

/*
 ** @brief      Get the next line of text available on a file descriptor.
 **
 ** Calling get_next_line in a loop will allow us to read the text available on
 ** the file descriptor one line at a time until the end of it.
 **
 ** A line is defined as a NUL or LF terminated string.
 **
 ** @param[in]  fd the file descriptor.
 ** @param[out] temp a static pointer to the next line to be read or NULL.
 ** @return     The first line to be read from temp.
 */

char	*get_next_line(int fd)
{
	static char	*temp[OPEN_MAX];

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp[fd])
		temp[fd] = ft_strdup("");
	if (!temp[fd])
		return (NULL);
	temp[fd] = ft_read (temp[fd], fd);
	if (!temp[fd])
		return (NULL);
	if (!*temp[fd])
	{
		free (temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	return (ft_next(&temp[fd]));
}
