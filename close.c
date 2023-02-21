/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:47:31 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 16:12:25 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_process *proc, int argc, int check_parent)
{
	int	i;

	i = -1;
	while (++i < argc - 4 && proc->flags)
	{
		if (i == proc->cmd - 2 && !check_parent)
		{
			if (proc->cmd == 2 || proc->cmd == argc - 2)
				continue ;
			close (proc->fds[i - 1][WRITE]);
			close (proc->fds[i][READ]);
		}
		else
		{
			if (i == proc->cmd - 3 && !check_parent)
				continue ;
			close (proc->fds[i][READ]);
			close (proc->fds[i][WRITE]);
		}
	}
	if (!proc->flags)
		close_fd (proc);
}

void	close_fd(t_process *proc)
{
	if (proc->cmd == 2)
		close (proc->fd[READ]);
	else if (proc->cmd == 3)
		close (proc->fd[WRITE]);
	else
	{
		close (proc->fd[READ]);
		close (proc->fd[WRITE]);
	}
}
