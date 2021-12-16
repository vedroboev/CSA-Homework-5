#ifndef CSA_HOMEWORK_5__BARBERSHOP_H_
#define CSA_HOMEWORK_5__BARBERSHOP_H_

// HEADERS.

#include "stdio.h" // NOLINT
#include "stdlib.h" // NOLINT
#include "unistd.h"
#include "semaphore.h"
#include "pthread.h"

// VARIABLES.

extern const int max_customer_count;

extern int haircut_time_bound;
extern int day_duration;
extern int total_customer_count;
extern int waiting_room_customer_count;

// SEMAPHORE VARIABLES.

extern sem_t customers_waiting;

extern pthread_mutex_t incrementing;
extern pthread_mutex_t cutting;
extern pthread_mutex_t busy;
extern pthread_mutex_t leaving;

void initializeSemaphores();

// UTILITY METHODS.

void cutHair();
void getHaircut(int customer_index);

// MAIN HANDLER METHODS.

void *barber(void *parameter);
void *customer(void *parameter);

#endif //CSA_HOMEWORK_5__BARBERSHOP_H_
