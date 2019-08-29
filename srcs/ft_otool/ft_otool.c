/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:21:19 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/29 16:21:20 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <ft_nm_otool.h>

# define ERROR			0
# define MH_MAGIC_64	0xfeedfacf

bool		open_file(char *file);
bool		check_usage(int argc, char **argv);
bool		print_usage(void);

int		main(int argc, char **argv)
{
	size_t	files;

	files = 0;
	if (!check_usage(argc, argv))
		return (print_usage());
	while (open_file(argv[++files]))
		;
	return (1);
}

# define BUFF	28

bool	open_file(char *file)
{
	int		fd;
	int		ret;
	char	buff[BUFF];

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERROR);
	ret = BUFF;


	int tmp;
	int	all = 0;
	//read(fd, buff, 28);


	while (ret == BUFF)
	{
		tmp = 0;
		ret = read(fd, buff, BUFF);
		//printf("[%i] ", ret);
		write(1, "[", 1);
		while (tmp < BUFF)
		{
			if (buff[tmp] == 0)
				write(1, ".", 1);
			else if (buff[tmp] == '\n' || buff[tmp] == '\t'
				|| buff[tmp] == '\r' || buff[tmp] == '\v'
				|| buff[tmp] == '\f')
				write(1, "|", 1);
			else if (buff[tmp] > 0)
				write(1, &buff[tmp], 1);
			else
				write(1, ",", 1);
			tmp++;
		}
		write(1, "]\n", 2);
		all += tmp;
	}
	printf("[%i]\n", all);
	printf("[%lu]\n", sizeof(t_segment));
	//55 48 89 	e5 48 83 ec 20 c7 45 fc 00 00 00 00 89
	//85 72 137 229

	if (close(fd) == -1)
		return (ERROR);
	return (1);
}

bool	check_usage(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (1);
}

bool		print_usage()
{
	write(1, "STOP\n", 5);
	return (0);
}
