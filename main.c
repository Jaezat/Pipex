/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:16:52 by mariacos          #+#    #+#             */
/*   Updated: 2025/10/11 15:12:58 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	struct s_all_argv	myargs;

	if (argc != 5)
	{
		write(2, "Not valid.\nUsage: file[0] cmd1 cmd2 file[1]", 43);
		return (1);
	}
	if (!envp || !envp[0])
		exit(EXIT_FAILURE);
	myargs.infile = argv[1];
	myargs.cmd1 = argv[2];
	myargs.cmd2 = argv[3];
	myargs.outfile = argv[4];
	myargs.envp = envp;
	return (pipex(&myargs));
}
