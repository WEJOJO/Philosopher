/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:23:04 by nhwang            #+#    #+#             */
/*   Updated: 2022/08/25 20:56:18 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

typedef struct s_philo
{
	struct s_data	*mdata;
	pthread_t		thread;
	int				id;
	int				first;
	int				last;
	long long		last_eat_time;
	int				eat_count;
}				t_philo;

typedef struct s_data
{
	int				num_of_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
	int				finish;
	int				finished_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	f_eatcontrol;
}				t_data;

long long	ft_atoi(char *str);
long long	ft_get_time(void);
int			print_error(char *msg);

void		ft_delay_time(long long wait_time, t_data *tdata);
int			ft_print_mut(t_data *tdata, int id, char *msg);
int			ft_philo_eat(t_data *tdata, t_philo *philo, int first, int last);

int			ft_set_param_mutex(t_data *tdata);
int			ft_set_param(t_data *tdata, int argc, char *argv[]);
int			ft_set_philo(t_philo **philo, t_data *tdata);
void		*ft_threadone(void *philo);
int			ft_onethread(t_philo *philo);

int			ft_free_thread(t_data *tdata, t_philo *philo);
void		ft_check_finish(t_data *tdata, t_philo *philo);
void		*ft_thr(void *philo);
int			ft_makethr(t_data *tdata, t_philo *philo);

#endif