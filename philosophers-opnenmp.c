#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

const int NB_PHILO = 5;
const int TIME_MAX_THINKING = 10;
const int TIME_MAX_EATING = 5;

// process of actions a philosopher goes through
void philo_process(int thread_num, omp_lock_t *left_fork, omp_lock_t *right_fork){

    //one philo behaves differently
    if (thread_num == 2){

        omp_set_lock(right_fork);
        printf("Philosopher %d picked up his right fork\n", thread_num);
        omp_set_lock(left_fork);
        printf("Philosopher %d picked up his left fork\n", thread_num);
        printf("Philosopher %d started to eat\n", thread_num);

    //rest of philos
    } else {

        omp_set_lock(left_fork);
        printf("Philosopher %d picked up his left fork\n", thread_num);
        omp_set_lock(right_fork);
        printf("Philosopher %d picked up his right fork\n", thread_num);
        printf("Philosopher %d started to eat\n", thread_num);

    }

    //philosopher begins eating
    int eat_time = (rand() % TIME_MAX_EATING) + 1;
	sleep(eat_time);
    printf("Philosopher %d is done eating\n", thread_num);
    //philosopher releases forks 
    omp_unset_lock(left_fork);
    omp_unset_lock(right_fork);
    printf("Philosopher %d released the forks\n", thread_num);

    //philosopher thinks for some time
    int think_time = (rand() % TIME_MAX_THINKING) + 1;
    sleep(think_time);   


}

int main(int argc, char **argv){

    omp_lock_t forks[NB_PHILO]; //array of locks representing the forks

    //initialize locks 
	for (int i = 0; i < NB_PHILO; i++){
        omp_init_lock(&forks[i]);
    }

    // one thread per philosopher	
    omp_set_num_threads(NB_PHILO);
    #pragma omp parallel 
    {
        int thread_num = omp_get_thread_num();

        //assign forks 
        omp_lock_t *left_fork = &forks[thread_num];
	    omp_lock_t *right_fork = &forks[(thread_num + 1) % NB_PHILO];

        while(1){
            philo_process(thread_num, left_fork, right_fork);
        }
    }

    return 0;    
    
}