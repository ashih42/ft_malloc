/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 19:28:00 by ashih             #+#    #+#             */
/*   Updated: 2018/08/14 02:10:25 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** This is the actual size to ask mmap()
** It includes sizeof(t_zone) and sizeof(t_block)
*/

void			*new_zone(size_t size)
{
	t_zone		*zone;
	t_block		*block;
	char		*str;

	if ((zone = mmap(0, size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	str = "LARGE";
	str = (size == (size_t)SMALL_ZONE_SIZE) ? "TINY" : str;
	str = (size == (size_t)LARGE_ZONE_SIZE) ? "SMALL" : str;
	VERBOSE_PRINT("  {green}mmap : %s zone at %p ( size=%lu ){reset}\n",
		str, zone, size);
	zone->next = NULL;
	zone->end = (void *)zone + size;
	block = (void *)zone + sizeof(t_zone);
	block->size = size - sizeof(t_zone) - sizeof(t_block);
	block->free = 1;
	block->next = NULL;
	block->checksum = (size_t)block + block->size;
	return (zone);
}

/*
** Add new zone z at beginning of list
** If success, return pointer to z
** If fail, return NULL
*/

void			*add_zone(t_zone **head, t_zone *z)
{
	if (!head || !z)
		return (NULL);
	if (!*head)
		*head = z;
	else
	{
		z->next = *head;
		*head = z;
	}
	return (z);
}
