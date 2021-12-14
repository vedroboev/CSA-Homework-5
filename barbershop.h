#ifndef CSA_HOMEWORK_5__BARBERSHOP_H_
#define CSA_HOMEWORK_5__BARBERSHOP_H_

#include "pthread.h"
#include "semaphore.h"
#include "stdlib.h" // NOLINT
#include "unistd.h"


class Barbershop {
private:
    int average_cutting_time;
    int total_customer_count;
    int waiting_room_count;
    sem_t customers_waiting;
    pthread_mutex_t cutting;
    pthread_mutex_t incrementing;
public:
    explicit Barbershop(int average_cutting_time);

    void *barber();
    void *customer();

    void cutHair();
    void getHaircut();
};

#endif //CSA_HOMEWORK_5__BARBERSHOP_H_
