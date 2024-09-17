/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:52:09 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 17:17:06 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_countsize(long int n)
{
	if (n < 0)
		return (1 + ft_countsize(-n));
	if ((n / 10) == 0)
		return (1);
	else
		return (1 + ft_countsize(n / 10));
}

void	ft_convbase(long int n, char *number, long int i)
{
	if (n < 0)
	{
		number[0] = '-';
		n *= -1;
	}
	if (n >= 10)
		ft_convbase((n / 10), number, (i - 1));
	number[i] = (n % 10) + 48;
}

char	*ft_itoa(int n)
{
	char		*number;
	long int	len;

	len = ft_countsize(n);
	number = (char *)malloc((len + 1) * sizeof(char));
	if (!number)
		return (NULL);
	number[len--] = '\0';
	ft_convbase(n, number, len);
	return (number);
}
