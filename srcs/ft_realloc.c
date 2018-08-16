/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 01:34:11 by ashih             #+#    #+#             */
/*   Updated: 2018/08/14 01:50:11 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		shrink_block(size_t size, t_block *block, t_zone *zone)
{
	block->size = size;
	block->checksum = (size_t)block + block->size;
	init_next_block(zone, block);
}
