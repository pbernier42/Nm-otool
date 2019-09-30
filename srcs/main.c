/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_otool.c                                       :+:      :+:    :+:   */
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
	t_flags	flags;
	int		files;

	if ((files = check_usage(argc, argv, &flags, ft_otool)) == RETURN_FAIL)
		return (RETURN_FAIL);
	while (argv[files] && !open_file(argv[files], &flags))
		++files;
	return (RETURN_SUCESS);
}
