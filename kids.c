/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:08:04 by mariacos          #+#    #+#             */
/*   Updated: 2025/10/11 13:06:21 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup_child_data(struct s_commands *cmds)
{
	if (cmds->full_path_cmd[0])
		free(cmds->full_path_cmd[0]);
	if (cmds->full_path_cmd[1])
		free(cmds->full_path_cmd[1]);
	if (cmds->argv_cmd[0])
		free_split(cmds->argv_cmd[0]);
	if (cmds->argv_cmd[1])
		free_split(cmds->argv_cmd[1]);
}

void	execute_first_child(int fd[2], int file_in_out[2],
		struct s_exec_data *execd, struct s_commands *cmds)
{
	close(fd[0]);
	if (file_in_out[1] != -1)
		close(file_in_out[1]);
	if (!execd->full_path_cmd || file_in_out[0] < 0)
	{
		close(fd[1]);
		if (file_in_out[0] != -1)
			close(file_in_out[0]);
		if (!execd->full_path_cmd && execd->argv_cmd && execd->argv_cmd[0])
		{
			write(2, execd->argv_cmd[0], ft_strlen(execd->argv_cmd[0]));
			write(2, ": command not found\n", 20);
		}
		cleanup_child_data(cmds);
		exit(127);
	}
	dup2(file_in_out[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(file_in_out[0]);
	close(fd[1]);
	execve(execd->full_path_cmd, execd->argv_cmd, execd->envp);
	cleanup_child_data(cmds);
	exit(126);
}

void	execute_second_child(int fd[2], int file_in_out[2],
		struct s_exec_data *execd, struct s_commands *cmds)
{
	close(fd[1]);
	if (file_in_out[0] != -1)
		close(file_in_out[0]);
	dup2(fd[0], STDIN_FILENO);
	dup2(file_in_out[1], STDOUT_FILENO);
	close(fd[0]);
	close(file_in_out[1]);
	if (!execd->full_path_cmd)
	{
		if (execd->argv_cmd && execd->argv_cmd[0])
		{
			write(2, execd->argv_cmd[0], ft_strlen(execd->argv_cmd[0]));
			write(2, ": command not found\n", 20);
		}
		cleanup_child_data(cmds);
		exit(127);
	}
	execve(execd->full_path_cmd, execd->argv_cmd, execd->envp);
	perror("execve");
	cleanup_child_data(cmds);
	exit(126);
}

int	create_children(struct s_all_argv *args, int fd[2],
		int file_in_out[2], struct s_commands *cmds)
{
	struct s_exec_data	execd[2];
	pid_t				child1;
	pid_t				child2;
	int					status;

	give_values_execd(&execd[0], cmds->full_path_cmd[0],
		cmds->argv_cmd[0], args->envp);
	give_values_execd(&execd[1], cmds->full_path_cmd[1],
		cmds->argv_cmd[1], args->envp);
	child1 = fork();
	if (child1 < 0)
		return (-1);
	else if (child1 == 0)
		execute_first_child(fd, file_in_out, &execd[0], cmds);
	child2 = fork();
	if (child2 < 0)
		return (-1);
	else if (child2 == 0)
		execute_second_child(fd, file_in_out, &execd[1], cmds);
	close_all_fds(fd, file_in_out);
	waitpid(child1, NULL, 0);
	waitpid(child2, &status, 0);
	return (WEXITSTATUS(status));
}

void	close_all_fds(int fd[2], int file_in_out[2])
{
	close(fd[0]);
	close(fd[1]);
	if (file_in_out[0] != -1)
		close(file_in_out[0]);
	if (file_in_out[1] != -1)
		close(file_in_out[1]);
}
