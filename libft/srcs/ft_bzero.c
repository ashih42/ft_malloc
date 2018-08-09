/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:53:42 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 10:54:22 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *buffer;

	buffer = s;
	while (buffer < ((unsigned char *)s) + n && (long long)buffer & 0b111)
		*buffer++ = 0;
	while (buffer + 32 <= ((unsigned char *)s) + n)
	{
		((unsigned long long *)buffer)[0] = 0;
		((unsigned long long *)buffer)[1] = 0;
		((unsigned long long *)buffer)[2] = 0;
		((unsigned long long *)buffer)[3] = 0;
		buffer += 32;
	}
	while (buffer + 8 <= ((unsigned char *)s) + n)
	{
		((unsigned long long *)buffer)[0] = 0;
		buffer += 8;
	}
	while (buffer < ((unsigned char *)s) + n)
		*buffer++ = 0;
}
