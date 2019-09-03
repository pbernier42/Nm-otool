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

# include <ft_otool.h>

int		main(int argc, char **argv)
{
	size_t	files;
	int		ret;

	files = 1;
	if (check_usage(argc, argv))
		return (RETURN_FAIL);
	while (argv[files] && !(ret = read_file(argv[files])))
		++files;
	return (RETURN_SUCESS);
}

int		check_usage(int argc, char **argv)
{
	if (argc < 2)
		return (error_usage());
	(void)argv;
	return (RETURN_SUCESS);
}
