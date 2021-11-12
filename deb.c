#include "philo.h"

typedef struct s_t
{
    pthread_t tp;
    pthread_t tm;
    pthread_mutex_t lock;

}   t_t;

void   *p(t_t *t)
{
    printf("ptest!\n");
    return (0);
}

void   *m(t_t *t)
{
    printf("mtest!\n");
    pthread_join(t->tp, NULL);
    printf("m-조인헀다!\n");
    pthread_mutex_lock(&t->lock);
    printf("m-락풀기!\n");
    return (0);
}

int main(){
    int i=0;
    t_t t;

    pthread_mutex_init(&t.lock, NULL);
    pthread_mutex_lock(&t.lock);
    pthread_create(&t.tp, NULL, (void*)&p, &t);
    pthread_create(&t.tm, NULL, (void*)&m, &t);
    pthread_detach(t.tm);
    sleep(1);
    printf("hello\n");
    printf("hello\n");
    // pthread_mutex_unlock(&t.lock);
    pthread_mutex_destroy(&t.lock);
// pthread_join(t.tm, NULL);
    sleep(1);
    i++;
    printf("hollo\n");
    printf("hello\n");
    i++;
    printf("hello %d\n", i);
}