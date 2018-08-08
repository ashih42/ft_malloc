/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 21:04:29 by ashih             #+#    #+#             */
/*   Updated: 2018/08/07 22:24:42 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void	*ret;

	ret = ft_malloc(size);
	if (ret && ptr)
		ft_memcpy(ret, ptr, size);
	ft_free(ptr);
	return (ret);
}
