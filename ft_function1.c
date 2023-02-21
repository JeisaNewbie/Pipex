/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:42:23 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 17:04:19 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	int				i;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (n && (string1[i] == string2[i]))
	{
		if (string1[i] == '\0' && string2[i] == '\0')
			break ;
		i++;
		n--;
	}
	if (n == 0)
		return (string1[i - 1] - string2[i - 1]);
	return (string1[i] - string2[i]);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	int		i;

	tmp = malloc(size * count);
	if (tmp == 0)
		return (0);
	i = size * count;
	ft_bzero (tmp, i);
	return (tmp);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset (s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	a;
	unsigned char	*tmp;

	a = (unsigned char)c;
	tmp = (unsigned char *)b;
	while (len)
	{
		*tmp = a;
		tmp++;
		len--;
	}
	return (b);
}

int	check_file(t_process *proc, int argc, char *argv)
{
	int	check;

	check = open (argv, O_RDONLY);
	if (check < 0)
	{
		write (2, "no such file or directory\n", 26);
		close_fds (proc, argc, 0);
		if (proc->flags)
		{
			close (proc->fds[0][READ]);
			close (proc->fds[0][WRITE]);
		}
		else
			close (proc->fd[WRITE]);
		exit (1);
	}
	return (check);
}
