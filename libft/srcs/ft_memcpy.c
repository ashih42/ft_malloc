/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 11:22:03 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 13:25:01 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	d = dst;
	s = (unsigned char *)src;
	while (d < ((unsigned char *)dst) + n && (long long)d & 0b111)
		*d++ = *s++;
	while (d + 32 <= ((unsigned char *)dst) + n)
	{
		((unsigned long long *)d)[0] = ((unsigned long long *)s)[0];
		((unsigned long long *)d)[1] = ((unsigned long long *)s)[1];
		((unsigned long long *)d)[2] = ((unsigned long long *)s)[2];
		((unsigned long long *)d)[3] = ((unsigned long long *)s)[3];
		d += 32;
		s += 32;
	}
	while (d + 8 <= ((unsigned char *)dst) + n)
	{
		((unsigned long long *)d)[0] = ((unsigned long long *)s)[0];
		d += 8;
		s += 8;
	}
	while (d < ((unsigned char *)dst) + n)
		*d++ = *s++;
	return (dst);
}
