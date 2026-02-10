/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:36:20 by mariacos          #+#    #+#             */
/*   Updated: 2025/10/11 13:09:07 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_variable(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strdup(envp[i] + 5));
		i++;
	}
	return (NULL);
}

char	*create_path_command(char *cmd, char **envp)
{
	char	*path;
	char	**dirs;
	char	**argv;
	char	*executable;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_path_variable(envp);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	free(path);
	if (!dirs)
		return (NULL);
	argv = ft_split(cmd, ' ');
	if (!argv || !argv[0])
	{
		free_split(dirs);
		free_split(argv);
		return (NULL);
	}
	executable = find_executable(dirs, argv[0]);
	free_split(dirs);
	free_split(argv);
	return (executable);
}

int	check_access_cmd(char *dir, char *command, char **full_path)
{
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		exit(EXIT_FAILURE);
	*full_path = ft_strjoin(tmp, command);
	if (!*full_path)
		exit(EXIT_FAILURE);
	free(tmp);
	if (access(*full_path, X_OK) == 0)
		return (1);
	free(*full_path);
	*full_path = NULL;
	return (0);
}

char	*find_executable(char **dirs, char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	if (!dirs || !command)
		return (NULL);
	while (dirs[i])
	{
		if (check_access_cmd(dirs[i], command, &full_path))
			return (full_path);
		i++;
	}
	return (NULL);
}

int	prepare_commands(struct s_all_argv *args, struct s_commands *cmds)
{
	cmds->full_path_cmd[0] = create_path_command(args->cmd1, args->envp);
	cmds->full_path_cmd[1] = create_path_command(args->cmd2, args->envp);
	cmds->argv_cmd[0] = ft_split(args->cmd1, ' ');
	cmds->argv_cmd[1] = ft_split(args->cmd2, ' ');
	if (!cmds->argv_cmd[0] || !cmds->argv_cmd[1])
	{
		if (cmds->argv_cmd[0])
			free_split(cmds->argv_cmd[0]);
		if (cmds->argv_cmd[1])
			free_split(cmds->argv_cmd[1]);
		if (cmds->full_path_cmd[0])
			free(cmds->full_path_cmd[0]);
		if (cmds->full_path_cmd[1])
			free(cmds->full_path_cmd[1]);
		return (-1);
	}
	return (0);
}
