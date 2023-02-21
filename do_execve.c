/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:50:43 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 22:58:49 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_path(t_process *proc, char **argv)
{
	char	**tmp;
	char	**execve_option;
	char	*path_cmd;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	execve_option = get_option (proc, argv);
	while (argv[proc->cmd][i[0]] != ' ' && argv[proc->cmd][i[0]] != '\0')
		i[0]++;
	path_cmd = ft_substr (argv[proc->cmd], 0, i[0], 0);
	i[0] = 0;
	while (ft_strncmp (proc->envp[i[0]], "PATH", 4))
		i[0]++;
	while (proc->envp[i[0]][i[1]] != '=')
		i[1]++;
	tmp = ft_split (&proc->envp[i[0]][++i[1]], ':');
	do_execve (proc, tmp, execve_option, path_cmd);
}

void	do_execve(t_process *proc, char **tmp, char **option, char *path_cmd)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		proc->path_cmd = ft_strjoin (tmp[i], path_cmd);
		execve (proc->path_cmd, option, proc->envp);
		free (proc->path_cmd);
		i++;
	}
	if (execve (path_cmd, option, proc->envp) < 0)
		write (2, "command not found\n", 18);
	exit (127);
}

char	**get_option(t_process *proc, char **argv)
{
	char	**option;
	int		flags;
	int		i;

	flags = 0;
	i = 0;
	while (argv[proc->cmd][i] != ' ' && argv[proc->cmd][i] != '\0')
		i++;
	if (argv[proc->cmd][i] == ' ')
	{
		flags = 1;
		if (argv[proc->cmd][i + 1] == '\'')
			flags = 2;
	}
	if (flags > 0)
		option = make_option (argv[proc->cmd], flags, 4);
	else
		option = make_option (argv[proc->cmd], flags, 3);
	return (option);
}

char	**make_option(char *argv, int flags, int type_of_cmd)
{
	char	**option;
	int		i;
	int		j;

	option = (char **) ft_calloc (type_of_cmd, sizeof (char *));
	if (option == NULL)
		exit (1);
	i = 0;
	while (argv[i] != ' ')
		i++;
	option[0] = ft_substr (argv, 0, i, 1);
	if (flags > 0)
	{
		j = ++i + 1;
		while (argv[j] != '\'' && argv[j] != '\0')
			j++;
		if (flags == 2)
			i++;
		option[1] = ft_substr (argv, i, j, flags);
		option[2] = STDIN_FILENO;
	}
	else
		option[1] = STDIN_FILENO;
	return (option);
}
