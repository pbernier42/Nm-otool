/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:12:09 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/03 17:12:11 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

void		print_address(t_ull adress, short size, bool ox)
{
	char		ret[size];
	short		len;

	len = size;
	while (len--)
	{
		ret[len] = CHAR_HEXA[adress % 16];
		adress /= 16;
	}
	if (ox)
		write(1, "0x", 2);
	write(1, ret, size);
}

void	print_number(t_ull number)
{
	size_t	rest;
	char	letter;

	rest = number % 10;
	if (number >= 10)
		print_number(number /= 10);
	else
		number /= 10;
	letter = rest + '0';
	write(1, &letter, 1);
}
