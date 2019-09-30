/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:21:09 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/29 16:21:13 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <ft_nm.h>

int		main(int argc, char **argv)
{
	t_flags	flags;
	int		files;

	if ((files = check_usage(argc, argv, &flags, ft_nm)) == RETURN_FAIL)
		return (RETURN_FAIL);

	return (RETURN_SUCESS);
}
