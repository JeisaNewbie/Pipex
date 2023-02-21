/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:11 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 22:52:51 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_two_cmd(t_process *proc, int argc, char **argv)
{
	if (proc->cmd == 2)
		do_firstcmd (proc, argc, argv);
	else
		do_lastcmd (proc, argc, argv);
}

void	do_cmd(t_process *proc, int argc, char **argv)
{
	if (proc->cmd == 2)
		do_firstcmd (proc, argc, argv);
	else if (proc->cmd == argc - 2)
		do_lastcmd (proc, argc, argv);
	else
		do_middlecmd (proc, argc, argv);
}

void	do_firstcmd(t_process *proc, int argc, char **argv)
{
	int	file;
	int	check_error;

	file = check_file (proc, argc, argv[1]);
	check_error = dup2 (file, STDIN_FILENO);
	close (file);
	if (check_error < 0)
		exit (1);
	close_fds (proc, argc, 0);
	if (proc->flags)
	{
		close (proc->fds[0][READ]);
		check_error = dup2 (proc->fds[0][WRITE], STDOUT_FILENO);
		close (proc->fds[0][WRITE]);
	}
	else
	{
		check_error = dup2 (proc->fd[WRITE], STDOUT_FILENO);
		close (proc->fd[WRITE]);
	}
	if (check_error < 0)
		exit (1);
	make_path (proc, argv);
}

void	do_lastcmd(t_process *proc, int argc, char **argv)
{
	int	file;
	int	check_error;

	close_fds (proc, argc, 0);
	if (proc->flags)
	{
		close (proc->fds[proc->cmd - 3][WRITE]);
		check_error = dup2 (proc->fds[proc->cmd - 3][READ], STDIN_FILENO);
		close (proc->fds[proc->cmd - 3][READ]);
	}
	else
	{
		check_error = dup2 (proc->fd[READ], STDIN_FILENO);
		close (proc->fd[READ]);
	}
	if (check_error < 0)
		exit (1);
	file = open (argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
		exit (1);
	check_error = dup2 (file, STDOUT_FILENO);
	if (check_error < 0)
		exit (1);
	close (file);
	make_path (proc, argv);
}

void	do_middlecmd(t_process *proc, int argc, char **argv)
{
	int	check_error;

	close_fds (proc, argc, 0);
	check_error = dup2 (proc->fds[proc->cmd - 3][READ], STDIN_FILENO);
	close (proc->fds[proc->cmd - 3][READ]);
	if (check_error < 0)
		exit (1);
	check_error = dup2 (proc->fds[proc->cmd - 2][WRITE], STDOUT_FILENO);
	close (proc->fds[proc->cmd - 2][WRITE]);
	if (check_error < 0)
		exit (1);
	make_path (proc, argv);
}
