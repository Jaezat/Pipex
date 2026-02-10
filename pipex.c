/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 08:32:51 by mariacos          #+#    #+#             */
/*   Updated: 2025/10/11 15:13:54 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(struct s_all_argv *args)
{
	struct s_commands	cmds;
	int					file_in_out[2];
	int					child_status;
	int					fd[2];

	ft_memset(&cmds, 0, sizeof(cmds));
	file_in_out[0] = open(args->infile, O_RDONLY);
	file_in_out[1] = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_opened_files(file_in_out[0],
		file_in_out[1], args->infile, args->outfile);
	if (creation_pipe(fd, file_in_out[0], file_in_out[1]) < 0)
		exit(1);
	if (prepare_commands(args, &cmds) < 0)
	{
		free_kids(&cmds);
		exit(1);
	}
	child_status = create_children(args, fd, file_in_out, &cmds);
	free(cmds.full_path_cmd[0]);
	free(cmds.full_path_cmd[1]);
	free_split(cmds.argv_cmd[0]);
	free_split(cmds.argv_cmd[1]);
	return (child_status);
}

void	give_values_execd(struct s_exec_data *execd,
		char *full_path_cmd, char **argv_cmd, char **envp)
{
	execd->full_path_cmd = full_path_cmd;
	execd->argv_cmd = argv_cmd;
	execd->envp = envp;
}

int	free_full_path(char *full_path1, char *full_path2)
{
	free(full_path1);
	free(full_path2);
	return (0);
}

void	free_kids(struct s_commands *cmds)
{
	if (!cmds)
	{
		free_split(cmds->argv_cmd[0]);
		free_split(cmds->argv_cmd[1]);
		free_full_path(cmds->full_path_cmd[0], cmds->full_path_cmd[1]);
		exit(1);
	}
}
