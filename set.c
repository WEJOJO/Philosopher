/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:23:23 by nhwang            #+#    #+#             */
/*   Updated: 2022/08/25 20:56:23 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_set_param_mutex(t_data *tdata)
{
	int	i;

	if (pthread_mutex_init(&(tdata->print), NULL))
		return (1);
	if (pthread_mutex_init(&(tdata->f_eatcontrol), NULL))
		return (1);
	tdata->forks = malloc(sizeof(pthread_mutex_t) * tdata->num_of_p);
	if (!(tdata->forks))
		return (1);
	i = 0;
	while (i < tdata->num_of_p)
	{
		if (pthread_mutex_init(&(tdata->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_set_param(t_data *tdata, int argc, char *argv[])
{
	tdata->num_of_p = ft_atoi(argv[1]);
	tdata->time_to_die = ft_atoi(argv[2]);
	tdata->time_to_eat = ft_atoi(argv[3]);
	tdata->time_to_sleep = ft_atoi(argv[4]);
	tdata->start_time = ft_get_time();
	if (tdata->num_of_p <= 0 || tdata->time_to_die < 0 || tdata->time_to_eat < 0
		|| tdata->time_to_sleep < 0)
	{
		return (5);
	}
	if (argc == 6)
	{
		tdata->to_eat = ft_atoi(argv[5]);
		if (tdata->to_eat <= 0)
			return (6);
	}
	if (ft_set_param_mutex(tdata))
		return (1);
	return (0);
}

int	ft_set_philo(t_philo **philo, t_data *tdata)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * tdata->num_of_p);
	if (!(philo))
		return (1);
	while (i < tdata->num_of_p)
	{
		(*philo)[i].mdata = tdata;
		(*philo)[i].id = i;
		(*philo)[i].first = (i + 1) % tdata->num_of_p;
		(*philo)[i].last = i;
		(*philo)[i].last_eat_time = ft_get_time();
		(*philo)[i].eat_count = 0;
		if (i % 2)
		{
			(*philo)[i].first = i;
			(*philo)[i].last = (i + 1) % tdata->num_of_p;
		}
		i++;
	}
	return (0);
}

void	*ft_threadone(void *philo)
{
	t_data	*tdata;
	t_philo	*tphilo;

	tphilo = philo;
	tdata = tphilo->mdata;
	usleep(1000 * tdata->time_to_die);
	printf("%d 1 died\n", tdata->time_to_die);
	return (0);
}

int	ft_onethread(t_philo *philo)
{
	if (pthread_create(&(philo[0].thread), NULL, ft_threadone, &(philo[0])))
		return (1);
	if (pthread_join(philo[0].thread, NULL))
		return (1);
	return (0);
}
