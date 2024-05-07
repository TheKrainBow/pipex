/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:30:12 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/07 09:54:59 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_path(args[0], env);
	if (path)
	{
		free(args[0]);
		args[0] = path;
	}
	if (execve(args[0], args, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		ft_free_tab(args);
		exit(1);
	}
}

void	child(char **av, int *pipe, char **env)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, 0);
	dup2(pipe[1], 1);
	close(pipe[0]);
	exec_cmd(av[2], env);
}

void	parent(char **av, int *pipe, char **env)
{
	int		fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit(1);
	dup2(fd, 1);
	dup2(pipe[0], 0);
	close(pipe[1]);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		exit(1);
	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
		child(av, p_fd, env);
	parent(av, p_fd, env);
}
