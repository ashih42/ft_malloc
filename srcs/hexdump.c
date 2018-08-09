/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 08:26:40 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 22:09:01 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			ft_putbyte(unsigned char c)
{
	if (' ' <= c && c <= '~')
		ft_putchar(c);
	else
		ft_putchar('.');
}

static void			ft_puthex(unsigned char c)
{
	static char		*hextable = "0123456789abcdef";

	ft_putchar(hextable[c / 16]);
	ft_putchar(hextable[c % 16]);
	ft_putchar(' ');
}

static void			hexdump_row(unsigned char *c, size_t num)
{
	size_t			left;
	size_t			i;

	ft_printf("      ");
	left = 0;
	i = 0;
	while (i < num)
	{
		ft_puthex(*(c + i++));
		left += 3;
	}
	while (++left <= ((CHARS_PER_ROW) * 3))
		ft_putchar(' ');
	ft_printf("| ");
	i = 0;
	while (i < num)
		ft_putbyte(*(c + i++));
	ft_putchar('\n');
}

void				hexdump(t_block *block)
{
	size_t			i;
	unsigned char	*c;
	size_t			num;

	i = 0;
	c = (unsigned char *)block + sizeof(t_block);
	num = block->size;
	while (num > 0)
	{
		hexdump_row(c, (num > CHARS_PER_ROW) ? CHARS_PER_ROW : num);
		num = (num > CHARS_PER_ROW) ? num - CHARS_PER_ROW : 0;
		c += CHARS_PER_ROW;
	}
}
