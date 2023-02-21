/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:10:14 by jhwang2           #+#    #+#             */
/*   Updated: 2023/02/20 17:02:50 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE	1024
# define READ			0
# define WRITE			1

typedef struct s_process
{
	pid_t	pid;
	char	*path_cmd;
	char	**envp;
	int		fd_idx;
	int		cmd;
	int		fd[2];
	int		**fds;
	int		flags;
}	t_process;

char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *b, int c, size_t len);
int			str_count(char *str, char c);
int			str_len(char **str, char c);
void		free_all(char **str);
char		*indiv_str(int str_len, char *str);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start,
				size_t len, int flags);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		free_proc(t_process *proc);
void		do_pipe(t_process *proc, int argc);
t_process	*init_proc(int argc);
int			do_fork(t_process *proc, int argc);
void		do_two_cmd(t_process *proc, int argc, char **argv);
void		do_cmd(t_process *proc, int argc, char **argv);
int			check_file(t_process *proc, int argc, char *argv);
void		do_firstcmd(t_process *proc, int argc, char **argv);
void		do_lastcmd(t_process *proc, int argc, char **argv);
void		do_middlecmd(t_process *proc, int argc, char **argv);
void		make_path(t_process *proc, char **argv);
void		do_execve(t_process *proc, char **tmp, char **option,
				char *path_cmd);
char		**get_option(t_process *proc, char **argv);
char		**make_option(char *argv, int flags, int type_of_cmd);
void		close_fd(t_process *proc);
void		close_fds(t_process *proc, int argc, int check_parent);
void		exit_proc(t_process *proc, int argc);

#endif