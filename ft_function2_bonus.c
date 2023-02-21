/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:44:49 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 15:45:48 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == 0 || s2 == 0)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (tmp == 0)
		return (0);
	tmp[0] = '\0';
	ft_strlcat(tmp, s1, len_s1 + 1);
	ft_strlcat(tmp, s2, len_s1 + len_s2 + 1);
	tmp[len_s1 + len_s2] = '\0';
	return (tmp);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	len_dns;
	size_t	size;

	len_src = 0;
	len_dst = 0;
	while (src[len_src] != '\0')
		len_src++;
	while (dst[len_dst] != '\0')
		len_dst++;
	len_dns = len_dst + len_src;
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	size = dstsize - len_dst - 1;
	while (*src != '\0' && size > 0)
	{
		dst[len_dst] = *src;
		src++;
		len_dst++;
		size--;
	}
	dst[len_dst] = '\0';
	return (len_dns);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, int flags)
{
	char	*tmp;

	if (s == 0)
		return (0);
	if (flags == 1)
		len--;
	tmp = (char *)malloc(sizeof(char) * (len + 2));
	if (tmp == NULL)
		exit (1);
	if (flags == 0)
	{
		tmp[0] = '/';
		ft_strlcpy (&tmp[1], &s[start], len + 1);
	}
	else
		ft_strlcpy (tmp, &s[start], len + 2);
	return (tmp);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	j = 0;
	while (src[count] != '\0')
		count++;
	if (dstsize == 0)
		return (count);
	while (j < dstsize - 1 && src[j] != '\0' && src[j] != '\'')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (count);
}
