#ifndef CSA_HOMEWORK_5__BARBERSHOP_H_
#define CSA_HOMEWORK_5__BARBERSHOP_H_

#include "stdio.h" // NOLINT
#include "stdlib.h" // NOLINT
#include "unistd.h"
#include "semaphore.h"
#include "pthread.h"

extern const int max_customer_count;
extern const int haircut_time_bound;

extern int total_customer_count;
extern int waiting_room_customer_count;

extern sem_t customers_waiting;

extern pthread_mutex_t incrementing;
extern pthread_mutex_t cutting;
extern pthread_mutex_t busy;

void cutHair();

void *barber(void *parameter);
void *customer(void *parameter);

#endif //CSA_HOMEWORK_5__BARBERSHOP_H_
