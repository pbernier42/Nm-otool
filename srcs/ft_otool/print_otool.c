/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:47:05 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/30 14:47:06 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <ft_otool.h>

void	print_count(long long count)
{
	char		ret[18];
	short		len;

	len = 17;
	while (len--)
	{
		ret[len] = HEXA_CHAR(count);
		count /= 16;
	}
	ret[17] = '\t';
	write (1, ret, 18);
}

void	print_data(unsigned char data[SIZE_BUFF], int read)
{
	char			ret[read * 3];
	short			len;

	len	= 0;
	while (len < read)
	{
		// if (data[len] == '\t' || data[len] == '\n' || data[len] == '\r' || data[len] == '\v' || data[len] == '\f')
		// 	ret[len] = '|';
		// else if (data[len] >= ' ')
		// 	ret[len] = data[len];
		// else
		// 	ret[len] = '.';

		ret[(len * 3)] = HEXA_CHAR(data[len] / 16);
		ret[(len * 3) + 1] = HEXA_CHAR(data[len]);
		ret[(len * 3) + 2] = len != (read - 1) ? ' ' : '\n';
		len++;
	}
	// ret[len] = '\n';
	// write(1, ret, read + 1);
	write(1, ret, read * 3);
}
