/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:51:46 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:52:35 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*construct_full_address_helper(const char *adr_element,
		const char *action, int adr_len, int ac_len)
{
	char	*final_address;

	final_address = safe_malloc(adr_len + ac_len + 2);
	ft_strlcpy(final_address, adr_element, adr_len + 1);
	ft_strlcpy(final_address + adr_len, "/", 2);
	ft_strlcpy(final_address + adr_len + 1, action, ac_len + 1);
	return (final_address);
}
