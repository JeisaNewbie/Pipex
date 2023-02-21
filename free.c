/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:25 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 15:53:13 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_proc(t_process *proc)
{
	int	i;

	i = 0;
	if (proc->fds)
	{
		while (i < proc->fd_idx)
			free (proc->fds[i++]);
		free (proc->fds);
	}
	free (proc);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		free (str[i]);
		i++;
	}
	free (str);
}
