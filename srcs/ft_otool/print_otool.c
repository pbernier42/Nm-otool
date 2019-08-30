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

# include <ft_nm_otool.h>

bool	print_usage()
{
	write(1, "STOP\n", 5);
	return (0);
}

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

void	print_data(unsigned char data[BUFF], int read)
{
	char			ret[read * 3];
	short			len;

	len	= 0;
	while (len < read)
	{
		ret[(len * 3)] = HEXA_CHAR(data[len] / 16);
		ret[(len * 3) + 1] = HEXA_CHAR(data[len]);
		ret[(len * 3) + 2] = len != (read - 1) ? ' ' : '\n';
		len++;
	}
	write(1, ret, read * 3);
}
