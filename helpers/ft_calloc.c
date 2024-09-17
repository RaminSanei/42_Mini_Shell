/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:30:36 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 17:17:02 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *str, size_t n)
{
	char	*suc;

	suc = (char *)str;
	while (n > 0)
	{
		*(suc++) = 0;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*b;

	b = malloc(size * count);
	if (!b)
		return (NULL);
	ft_bzero(b, size * count);
	return (b);
}
