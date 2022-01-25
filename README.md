# philosophers
The basics of threading a process with mutex.

# 실행 방법
- `make`
- `./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat(optional)]`

# the dining philosophers problem

philosopher with threads and mutex

![image](https://user-images.githubusercontent.com/75327385/150930425-56815ee8-b0d5-4495-98df-50ea6271c59f.png)

## 규칙

- 세 명의 philosopher가 다음의 행동을 한다: `eating`,  `sleeping`, `thinking`
- 한번에 한 행동만 한다.
- 포크 두개가 있어야 식사가 가능하다.
- eating → sleeping → thinking 순서로행동한다.
- 철학자가 죽으면 프로그램이 종료된다.
- 프로그램 옵션
    
    ```
    number_of_philosophers 
    time_to_die
    time_to_eat 
    time_to_sleep 
    [number_of_times_each_philosopher_must_eat]
    ```
    
    - `number_of_philosophers` (==number of forks)
        - 철학자들은 순서대로 앉아야 한다
    - `time_to_die` : in milliseconds, eating 후 죽지 않는 시간([time_to_die]ms 안에 식사를 해야함)
    - `time_to_eat` : eating 걸리는 시간
    - `time_to_sleep` : sleeping 걸리는 시간
    - `[number_of_times_each_philosopher_must_eat]` : 추가옵션, 철학자 모두가 n번 먹으면 프로그램이 종료됨.
- 철학자의 상태가 바뀔 때마다, 다음과 같이 출력된다.
    
    ◦ timestamp_in_ms X has taken a fork
    ◦ timestamp_in_ms X is eating
    ◦ timestamp_in_ms X is sleeping
    ◦ timestamp_in_ms X is thinking
    ◦ timestamp_in_ms X died
    
- 상태출력 시 다른 철학자와 꼬이면 안된다.
- 철학자가 죽고 나서 출력할 때까지 오차는 10ms 이내여야 한다.
- Philosophers should avoid dying! (교착상태 피하기) - 철학자가 thread다.
- 포크를 동시에 사용할 수 없도록 mutex 로 보호해놓기

#mutex #thread #deadlock(교착)
