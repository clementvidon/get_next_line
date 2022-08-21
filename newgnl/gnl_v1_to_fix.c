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

#include "get_next_line_bonus.h"

/*
 ** @brief      Extract the first line it finds in temp and update temp to pass
 **             to the next line it contains or NULL if there is nothing left to
 **             read.
 **
 ** @param[i/o] temp can be the next line [ and more ] or NULL.
 ** @return     A new temp starting from the next line to read or NULL.
 */

static char	*get_next_line_2(char **temp)
{
	char	*line;
	char	*ptr;

	if (**temp == '\0')
	{
		free (*temp);
		*temp = NULL;
		return (NULL);
	}
	ptr = *temp;
	while (*ptr != '\0' && *ptr != '\n')
		ptr++;
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
 ** @brief      Get the next line of text available on a file descriptor.
 **
 ** Calling get_next_line in a loop will allow us to read the text available on
 ** the file descriptor one line at a time until the end of it.
 **
 ** A line is defined as a NUL or LF terminated string.
 **
 ** @var        temp can be:
 **              - the next line, if BUFFER_SIZE is smaller than a line.
 **              - the next line and more, if BUFFER_SIZE is bigger than a line.
 **              - NULL if there are no text left to read on the filedes.
 ** @var        line is the next line to be returned.
 ** @var        buf is for read(2) buffer.
 ** @var        r is for read(2) return value.
 **
 ** @param[in]  fd the file descriptor.
 ** @return     The line that has just been read or NULL.
 */

char	*get_next_line(int fd)
{
	static char	*temp[OPEN_MAX];
	char		*buf;
	long		r;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp[fd])
		temp[fd] = ft_strdup ("");
	if (!temp[fd])
		return (NULL);
	buf = malloc (sizeof (*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(temp[fd]), NULL);
	r = 1;
	while (r && !ft_strchr (temp[fd], '\n'))
	{
		r = read (fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (free (buf), free (temp[fd]), NULL);
		buf[r] = '\0';
		temp[fd] = ft_strjoin_free_s1 (temp[fd], buf);
		if (!temp[fd])
			return (free (buf), NULL);
	}
	return (free (buf), get_next_line_2(temp));
}
