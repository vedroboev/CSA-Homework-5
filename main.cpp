#include "stdio.h" // NOLINT
#include "stdlib.h" // NOLINT
#include "unistd.h"
#include "semaphore.h"
#include "pthread.h"

const int max_customer_count = 100;
const int haircut_time_bound = 20;

int total_customer_count = 0;
int waiting_room_customer_count = 0;

sem_t customers_waiting;

pthread_mutex_t incrementing;
pthread_mutex_t cutting;
pthread_mutex_t sleeping;

void getHaircut() {
    printf("Haircut for customer %d started...", total_customer_count);
    // Picking a random haircut time.
    int time = rand() % 10 + 1; // NOLINT
    // Waiting unlit haircut end.
    sleep(time);
    printf("Haircut for customer %d finished! Total time: %d.", total_customer_count, time);
}

void barber(void* parameter) {
    printf("test");
    while (total_customer_count < 100){
        // Sleeping until a customer appears.
        sem_wait(&customers_waiting);

        // Waiting until modification is unlocked and locking it.
        pthread_mutex_lock(&incrementing);
        // Incrementing total visitor count, decrementing the number of people in the waiting room.
        waiting_room_customer_count--;
        total_customer_count++;

        // Unlocking modification and making barber available.
        pthread_mutex_unlock(&incrementing);
        pthread_mutex_unlock(&cutting);
    }
}
void *customer(void* parameter) {
    while (total_customer_count < 100){
        // Waiting until waiting room can be modified.
        pthread_mutex_lock(&incrementing);
        // Adding the current customer to the line.
        waiting_room_customer_count++;
        // Unlocking modification and incrementing waiting line.
        pthread_mutex_unlock(&incrementing);
        sem_post(&customers_waiting);
        // Waiting until the barber is available.
        pthread_mutex_lock(&cutting);
        // Getting the haircut.
        getHaircut();
    }
}

int main() {
    sem_init(&customers_waiting, 0, 0);
    pthread_mutex_init(&incrementing, nullptr);
    pthread_mutex_init(&cutting, nullptr);

    // Creating customers.
    pthread_t customers[10];

    for (unsigned long & i : customers) {
        pthread_create(&i, nullptr, customer, nullptr);
    }

    barber(nullptr);

    return 0;
}
