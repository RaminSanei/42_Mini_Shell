/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:02:50 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 15:48:49 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnjoin(char *s1, char *s2, int flag)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (flag == 4)
		result = ft_strdup(s2);
	else
		result = ft_strjoin(s1, s2);
	if (flag != 3 && s1)
		free(s1);
	if (flag > 1 && s2)
		free(s2);
	return (result);
}
