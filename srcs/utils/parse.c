/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:52:11 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/25 14:52:13 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

bool		same_text(char text[16], char check[16])
{
	short	i;

	i = 0;
	while (check[i] == text[i]
		&& check[i] && i < 16)
		++i;
	return ((i == 16 || !check[i]) ? true : false);
}

bool		sorted_text(char *text_one, char *text_two)
{
	size_t	len = 0;

	while (text_one[len] == text_two[len]
		&& text_one[len] && text_one[len] != '\0'
		&& text_two[len] && text_two[len] != '\0')
		++len;
	return (text_one[len] <= text_two[len] ? true : false);
}
