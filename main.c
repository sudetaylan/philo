/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:56:59 by staylan           #+#    #+#             */
/*   Updated: 2025/07/11 17:57:04 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc != 6 && argc != 5)
		return (1);
	if (!arg_control(argv))
		return (1);
	if (!init_tdata(argv, &data, argc))
		return (1);
	if (!init_tphilo(&data, &philo))
		return (1);
	handle_threads(&data, philo);
	destroy_mutex(&data, philo);
	return (0);
}
