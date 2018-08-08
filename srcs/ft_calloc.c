/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 21:04:30 by ashih             #+#    #+#             */
/*   Updated: 2018/08/07 22:24:46 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = ft_malloc(count * size);
	if (ret)
		ft_bzero(ret, count * size);
	return (ret);
}
