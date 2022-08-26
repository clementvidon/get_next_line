/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:00:00 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/15 18:00:00 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 ** @brief      Read an entire line from stream.
 **
 ** Read up to (and including) a newline from STREAM into *LINEPTR (and
 ** null-terminate it). *LINEPTR is a pointer returned from malloc (or NULL),
 ** pointing to *N characters of space.  It is realloc'd as necessary.  Returns
 ** the number of characters read (not including the null terminator), or -1 on
 ** error or EOF.
 **
 ** @copyright  1991 Free Software Foundation, Inc.
 **             This function is part of the GNU C Library.
 */

int	ft_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char	line[256];
	char		*ptr;
	size_t		len;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (ferror (stream))
		return (-1);
	if (feof (stream))
		return (-1);
	fgets (line, 256, stream);
	ptr = strchr (line, '\n');
	if (ptr)
		*ptr = '\0';
	len = strlen (line);
	if ((len + 1) < 256)
	{
		ptr = realloc (*lineptr, 256);
		if (ptr == NULL)
			return (-1);
		*lineptr = ptr;
		*n = 256;
	}
	strcpy (*lineptr, line);
	return ((int)len);
}

/*
 ** @brief      Read the given file and output its content on STDOUT line by
 **             line.
 */

int	main(int ac, char **av)
{
	char	*str;
	size_t	len;
	FILE	*file;

	if (ac != 3)
		return (write
			(2, "Usage: ./getline <path_to_file> <buffer_size>\n", 46), 1);
	if (strlen (av[1]) >= 100 || *av[2] == '-')
		return (write (2, "Error: argument\n", 16), 1);
	str = NULL;
	len = (size_t)atoi (av[2]);
	file = fopen (av[1], "r");
	if (!file)
		return (1);
	while (ft_getline (&str, &len, file) != -1)
		;
	write (1, str, strlen (str));
	fclose (file);
	if (str)
		free (str);
	return (0);
}
