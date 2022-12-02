/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:22:47 by nhwang            #+#    #+#             */
/*   Updated: 2022/08/25 21:06:02 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thr(void *philo)
{
	t_data		*tdata;
	t_philo		*tphilo;
	long long	ttime_to_sleep;

	tphilo = philo;
	tdata = tphilo->mdata;
	ttime_to_sleep = (long long)tdata->time_to_sleep;
	while (!tdata->finish)
	{
		ft_philo_eat(tdata, tphilo, tphilo->first, tphilo->last);
		if (tdata->to_eat == tphilo->eat_count)
		{
			pthread_mutex_lock(&(tdata->f_eatcontrol));
			tdata->finished_eat++;
			pthread_mutex_unlock(&(tdata->f_eatcontrol));
			break ;
		}
		ft_print_mut(tdata, tphilo->id, "is sleeping");
		ft_delay_time(ttime_to_sleep, tdata);
		ft_print_mut(tdata, tphilo->id, "is thinking");
		usleep(500);
	}
	return (0);
}

int	ft_free_thread(t_data *tdata, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < tdata->num_of_p)
		if (pthread_mutex_destroy(&(tdata->forks[i++])))
			return (1);
	free(philo);
	free(tdata->forks);
	if (pthread_mutex_destroy(&(tdata->print)))
		return (1);
	if (pthread_mutex_destroy(&(tdata->f_eatcontrol)))
		return (1);
	return (0);
}

void	ft_check_finish(t_data *tdata, t_philo *philo)
{
	int			i;
	long long	now;

	while (!tdata->finish)
	{
		if ((tdata->to_eat != 0) && (tdata->num_of_p == tdata->finished_eat))
			break ;
		i = -1;
		while (++i < tdata->num_of_p)
		{
			now = ft_get_time();
			if ((tdata->to_eat != 0) && (philo[i].eat_count == tdata->to_eat))
			{
				i++;
				continue ;
			}
			if ((now - philo[i].last_eat_time) >= tdata->time_to_die)
			{
				ft_print_mut(tdata, i, "died");
				tdata->finish = 1;
				break ;
			}
		}
	}
	tdata->finish = 1;
}

int	ft_makethr(t_data *tdata, t_philo *philo)
{
	int		i;
	int		j;

	j = -1;
	while (++j < 2)
	{
		i = j;
		while (i < tdata->num_of_p)
		{
			philo[i].last_eat_time = ft_get_time();
			if (philo[i].last_eat_time == -1)
				return (1);
			if (pthread_create(&(philo[i].thread), NULL, ft_thr, &(philo[i])))
				return (1);
			i = i + 2;
		}
	}
	ft_check_finish(tdata, philo);
	i = 0;
	while (i < tdata->num_of_p)
		if (pthread_join(philo[i++].thread, NULL))
			return (1);
	usleep(1000 * 500);
	return (ft_free_thread(tdata, philo));
}

int	main(int argc, char *argv[])
{
	t_data	tdata;
	t_philo	*philo;
	int		errcheck;

	if (argc != 5 && argc != 6)
		return (print_error("error param"));
	memset(&tdata, 0, sizeof(t_data));
	errcheck = ft_set_param(&tdata, argc, argv);
	if (errcheck)
		return (print_error("error setting param"));
	errcheck = ft_set_philo(&philo, &tdata);
	if (errcheck)
		return (print_error("error setting philo"));
	if (tdata.num_of_p == 1)
	{
		if (ft_onethread(philo))
			return (print_error("error make 1 thread"));
	}
	else
	{
		errcheck = ft_makethr(&tdata, philo);
		if (errcheck)
			return (print_error("error start philo"));
	}
	return (0);
}
