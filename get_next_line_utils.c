/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:00:00 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/15 18:00:00 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** Unmodified from Libft.
 */

#include "get_next_line.h"

/*
 ** @brief      Locate a character in string.
 **
 ** "The strchr() function locates the first occurrence of c (converted to a
 ** char) in the string pointed to by s.  The terminating null character is
 ** considered to be part of the string; therefore if c is ‘\0’, the functions
 ** locate the terminating ‘\0’."
 **
 ** @see        STRCHR(3) <string.h>
 */

char	*ft_strchr(char const *s, int c)
{
	while (*s && *s != (unsigned char)c)
		++s;
	if (*s == (unsigned char)c)
		return ((char *)s);
	else
		return (0);
}

/*
 ** @brief      Find length of string.
 **
 ** "The strlen() function computes the length of the string s.  The strnlen()
 ** function attempts to compute the length of s, but never scans beyond the **
 ** first maxlen bytes of s."
 **
 ** @see        STRLEN(3) <string.h>
 */

size_t	ft_strlen(char const *str)
{
	char const	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return ((size_t)(ptr - str));
}

/*
 ** @brief      Save a copy of a string.
 **
 ** "The strdup() function allocates sufficient memory for a copy of the string
 ** s1, does the copy, and returns a pointer to it.  The pointer may
 ** subsequently be used as an argument to the function free(3)."
 **
 ** @see        STRDUP(3) <string.h>
 */

char	*ft_strdup(char const *str)
{
	char	*dup;
	char	*ptr;

	dup = malloc (sizeof (*dup) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	ptr = dup;
	while (*str)
		*ptr++ = *str++;
	return (*ptr = 0, dup);
}

/*
 ** @brief      Concatenate two strings into a new string (with malloc).
 **
 ** @param[in]  s1 the first string (will be free).
 ** @param[in]  s2 the second string.
 ** @return     A string made of s1 + s2 or NULL if malloc fail.
 */

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*s3;
	char	*p3;
	char	*p1;

	s3 = malloc (sizeof (*s3) * (ft_strlen (s1) + ft_strlen (s2) + 1));
	if (!s3)
		return (free (s1), NULL);
	p3 = s3;
	p1 = s1;
	while (*p1)
		*p3++ = *p1++;
	while (*s2)
		*p3++ = *s2++;
	return (free (s1), *p3 = 0, s3);
}

/*
 ** @brief      Extract substring from string.
 **
 ** "Allocates (with malloc(3)) and returns a substring from the string s.
 ** The substring begins at index start and is of maximum size len."
 **
 ** @param[in]  str the string that contain the cherished substring.
 ** @param[in]  start the beginning of the substring.
 ** @param[in]  size the length of the substring.
 ** @return     The cherished substring or NULL if malloc fail.
 */

char	*ft_substr(const char *str, unsigned int start, size_t size)
{
	size_t	len;
	char	*sub;

	len = ft_strlen (str);
	if (start >= len)
		return (ft_strdup(""));
	if (len - start < size)
		size = len - start;
	sub = malloc (sizeof (*sub) * (size + 1));
	if (!sub)
		return (NULL);
	sub[size] = 0;
	while (size--)
		sub[size] = str[start + size];
	return (sub);
}
