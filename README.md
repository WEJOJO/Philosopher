# Notion_Link
[https://www.notion.so/Thread-philosopher-cfe8c6c2922f475bb41122510ae08099](https://kindly-koi-e00.notion.site/Thread-philosopher-cfe8c6c2922f475bb41122510ae08099)

![p_image](https://github.com/WEJOJO/Philosopher/assets/46590247/03d66346-b135-430f-967d-30a886b6a136)

# 주요 요구 사항
#### - 철학자 = Thread
- **철학자들을 최대한 살릴 것.**
- 철학자들은 **생각**(대기 상태)하거나 **식사**/**수면**을 하며 시간을 보냄.
- 먹지 못한 철학자는 인자로 받게되는 “**밥을 먹지 않고도 생존 가능한 시간**”을 초과하면 죽음.
- 각 철학자는 식사에 포크 **두 개**를 필요로 함.
- 하지만 테이블에는 포크가 **철학자의 수** 만큼 밖에 없음.
- 각 철학자는 **양 옆**에 있는 포크를 사용해 식사.
- 이 때, 포크가 **이미 사용 중**인 경우 다른 철학자가 사용할 때까지 **기다려야 함.**

# 200, 199 철학자의 생존 동작
## arg = (Thread, Time_to_die, Time_to_eat, Time_to_sleep)
------------------------------------------------------------------------------------------------------------------------------------------------

## 200 Thread (200, 500, 200, 200)

![Philo1](https://github.com/WEJOJO/Philosopher/assets/46590247/5aea140b-74f0-49ed-92aa-b1674067d7fd)


## 199 Thread (199, 700, 200, 200)
![Philo2](https://github.com/WEJOJO/Philosopher/assets/46590247/772afa74-aacf-4806-b667-179d4ec60eb7)



# 생존 불가 케이스의 죽음.
### (Time_to_die < Time_to_eat + Time_to_sleep) 
### || (스레드 짝수 && Time_to_die < Time_to_eat x 2) 
### || (스레드 홀수 && Time_to_die < Time_to_eat x 3)
------------------------------------------------------------------------------------------------------------------------------------------------
