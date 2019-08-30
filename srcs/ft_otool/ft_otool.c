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

int		main(int argc, char **argv)
{
	size_t	files;

	files = 0;
	if (!check_usage(argc, argv))
		return (print_usage());
	while (read_file(argv[++files]))
		;
	return (1);
}

bool	check_usage(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (1);
}
