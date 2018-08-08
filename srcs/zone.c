/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 19:28:00 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 07:27:18 by ashih            ###   ########.fr       */
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

	VERBOSE_PRINT("  new_zone ( size=%lu )\n", size);
	zone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
		-1, 0);
	if (zone == (void *)-1)
		return (NULL);
	zone->next = NULL;
	zone->end = (void *)zone + size;
	block = (void *)zone + sizeof(t_zone);
	block->size = size - sizeof(t_zone) - sizeof(t_block);
	block->free = 1;
	block->next = NULL;
	return (zone);
}

/*
** Add new zone z at beginning of list
** If success, return pointer to z
** If fail, return NULL
*/

void			*add_zone(t_zone **head, t_zone *z)
{
	if (!z || !head)
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
