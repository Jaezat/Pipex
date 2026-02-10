/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 08:32:57 by mariacos          #+#    #+#             */
/*   Updated: 2025/10/11 13:12:10 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// # include "../libft/libft.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

struct s_all_argv
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
	char	**envp;
};

struct s_commands
{
	char	*full_path_cmd[2];
	char	**argv_cmd[2];
};

struct s_exec_data
{
	char	*full_path_cmd;
	char	**argv_cmd;
	char	**envp;
};

int		pipex(struct s_all_argv *args);
int		create_children(struct s_all_argv *args, int fd[2],
			int file_in_out[2], struct s_commands *cmds);
int		creation_pipe(int *fd, int file1, int file2);
void	check_opened_files(int file1, int file2, char *infile, char	*outfile);
void	changing_directions(int input_fd, int output_fd);
void	close_files(int fd1, int fd2, int file1, int file2);
void	free_split(char **arr);
int		prepare_commands(struct s_all_argv *args, struct s_commands *cmds);
char	*get_path_variable(char **envp);
char	*find_executable(char **dirs, char *command);
int		free_full_path(char *full_path1, char *full_path2);
void	free_kids(struct s_commands *cmds);
int		check_access_cmd(char *dir, char *command, char **full_path);
void	give_values_execd(struct s_exec_data *execd,
			char *full_path_cmd, char **argv_cmd, char **envp);
void	execute_first_child(int fd[2], int file_in_out[2],
			struct s_exec_data *execd, struct s_commands *cmds);
void	execute_second_child(int fd[2], int file_in_out[2],
			struct s_exec_data *execd, struct s_commands *cmds);
void	close_all_fds(int fd[2], int file_in_out[2]);
void	cleanup_child_data(struct s_commands *cmds);

#endif
