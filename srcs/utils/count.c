/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:07:48 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/05 18:07:49 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

size_t		len_text(char *text)
{
	size_t	len;

	len = 0;
	while (text && text[len])
		++len;
	return (len);
}

short		size_number(t_ull number)
{
	short		len;

	len = 1;
	while (number /= 10)
		++len;
	return (len);
}
