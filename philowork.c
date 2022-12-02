/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philowork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:23:18 by nhwang            #+#    #+#             */
/*   Updated: 2022/08/25 20:56:17 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_delay_time(long long wait_time, t_data *tdata)
{
	long long	start;
	long long	now;

	start = ft_get_time();
	while (!(tdata->finish))
	{
		now = ft_get_time();
		if ((now - start) == wait_time)
			break ;
		usleep(500);
	}
}

int	ft_print_mut(t_data *tdata, int id, char *msg)
{
	long long	now;

	now = ft_get_time();
	if (now == -1)
	{
		return (-1);
	}
	pthread_mutex_lock(&(tdata->print));
	if (!(tdata->finish))
	{
		printf("%lld %d %s\n", now - tdata->start_time, id + 1, msg);
	}
	pthread_mutex_unlock(&(tdata->print));
	return (0);
}

int	ft_philo_eat(t_data *tdata, t_philo *philo, int first, int last)
{
	pthread_mutex_lock(&(tdata->forks[first]));
	ft_print_mut(tdata, philo->id, "has taken a fork");
	pthread_mutex_lock(&(tdata->forks[last]));
	ft_print_mut(tdata, philo->id, "has taken a fork");
	ft_print_mut(tdata, philo->id, "is eating");
	philo->last_eat_time = ft_get_time();
	philo->eat_count = philo->eat_count + 1;
	ft_delay_time((long long)tdata->time_to_eat, tdata);
	pthread_mutex_unlock(&(tdata->forks[first]));
	pthread_mutex_unlock(&(tdata->forks[last]));
	return (0);
}
