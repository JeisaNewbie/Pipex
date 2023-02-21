/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:11:39 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 23:18:00 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_process	*proc;

	if (argc < 5)
		return (1);
	proc = init_proc (argc);
	proc->envp = envp;
	do_pipe (proc, argc);
	if (do_fork (proc, argc))
		exit (1);
	if (proc->pid == 0)
	{
		if (proc->flags)
			do_cmd (proc, argc, argv);
		else
			do_two_cmd (proc, argc, argv);
	}
	else
	{
		close_fds (proc, argc, 1);
		exit_proc (proc, argc);
	}
}

void	exit_proc(t_process *proc, int argc)
{
	pid_t	pid;
	int		last_status;
	int		status;
	int		i;

	i = 0;
	last_status = 0;
	while (i < argc - 3)
	{
		status = 0;
		pid = wait (&status);
		if (pid > 0)
			i++;
		if (proc->pid == pid)
			last_status = WEXITSTATUS(status);
	}
	exit (last_status);
}

t_process	*init_proc(int argc)
{
	t_process	*tmp;

	tmp = (t_process *) malloc (sizeof (t_process));
	if (tmp == NULL)
		exit (1);
	tmp->pid = 1;
	tmp->cmd = 0;
	tmp->fd_idx = 0;
	tmp->flags = 0;
	if (argc - 3 > 2)
	{
		tmp->flags = 1;
		tmp->fds = (int **) malloc (sizeof (int *) * (argc - 4));
		if (tmp->fds == NULL)
			exit (1);
		while (tmp->fd_idx < argc - 4)
		{
			tmp->fds[tmp->fd_idx] = (int *) malloc (sizeof (int) * 2);
			if (tmp->fds[tmp->fd_idx++] == NULL)
				exit (1);
		}
	}
	tmp->path_cmd = "";
	return (tmp);
}

void	do_pipe(t_process *proc, int argc)
{
	int	i;

	i = 0;
	if (proc->flags == 0)
	{
		if (pipe (proc->fd) < 0)
			exit (1);
	}
	else
	{
		while (i < argc - 4)
		{
			if (pipe (proc->fds[i]) < 0)
				exit (1);
			i++;
		}
	}
}

int	do_fork(t_process *proc, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		if (proc->pid > 0)
			proc->pid = fork ();
		else
			return (0);
		if (proc->pid == 0)
			proc->cmd = i + 2;
		else if (proc->pid < 0)
			exit (1);
		i++;
	}
	return (0);
}
