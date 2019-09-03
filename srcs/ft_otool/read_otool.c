/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:12:29 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/30 16:12:31 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

// void 		print_header(t_header header);
// void 		print_segment(t_segment segment);

int		read_file(char *file)
{
	int				fd;


	if ((fd = open(file, O_RDONLY)) < 0 )
		return (error_otool(error_file(fd, file)));
	//read_header(fd);
	//read_data(fd);
	if (close(fd))
		return (error_otool(ERROR_FILE_CLOSE));
	return (RETURN_SUCESS);
}