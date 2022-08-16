/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:00:00 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/15 18:00:00 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

/*
 ** @brief      Read the given file and output it content on STDOUT line by
 **             line.
 */

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
		return (write (2, "Usage: ./get_next_line <path_to_file>\n", 30), 1);
	if (ft_strlen(av[1]) >= 1000)
	{
		write (2, "get_next_line: \033[31mFile name too long\n\033[0m\n", 43);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write (2, "get_next_line: \033[31mFile error\n\033[0m\n", 35);
		return (1);
	}
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
		{
			write (2, "get_next_line: \033[32mDone\n\033[0m\n", 25);
			return (0);
		}
		write (1, line, ft_strlen (line));
		free (line);
	}
}
