/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:13:19 by mariacos          #+#    #+#             */
/*   Updated: 2025/10/11 13:06:50 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	creation_pipe(int *fd, int file1, int file2)
{
	if (pipe(fd) < 0)
	{
		perror("pipe");
		if (file1 >= 0)
			close(file1);
		if (file2 >= 0)
			close(file2);
		return (-1);
	}
	return (0);
}

void	check_opened_files(int file1, int file2, char *infile, char *outfile)
{
	if (file1 < 0)
	{
		write(2, infile, ft_strlen(infile));
		if (access(infile, F_OK) == 0)
			write(2, ": Permission denied\n", 21);
		else
			write(2, ": No such file or directory\n", 28);
	}
	if (file2 < 0)
	{
		write(2, outfile, ft_strlen(outfile));
		if (access(outfile, F_OK) == 0)
			write(2, ": Permission denied\n", 21);
		else
			write(2, ": No such file or directory\n", 28);
		if (file1 >= 0)
			close(file1);
		exit(EXIT_FAILURE);
	}
}

void	changing_directions(int input_fd, int output_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input_fd");
		exit(EXIT_FAILURE);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output_fd");
		exit(EXIT_FAILURE);
	}
	if (input_fd != STDIN_FILENO && input_fd >= 0)
		close(input_fd);
	if (output_fd != STDOUT_FILENO && output_fd >= 0)
		close(output_fd);
}

void	close_files(int fd1, int fd2, int file1, int file2)
{
	if (file1 >= 0)
		close(file1);
	if (file2 >= 0)
		close(file2);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
