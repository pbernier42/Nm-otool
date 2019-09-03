/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:12:09 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/03 17:12:11 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

size_t		len_text(char *text)
{
	size_t	len;

	len = 0;
	while (text && text[len])
		++len;
	return (len);
}
