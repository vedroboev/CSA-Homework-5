#include "barbershop.h"

const int max_customer_count = 10;
const int haircut_time_bound = 10;

int total_customer_count = 0;
int waiting_room_customer_count = 0;
int new_customer_index = 0;

sem_t customers_waiting;

pthread_mutex_t incrementing;
pthread_mutex_t cutting;
pthread_mutex_t busy;
pthread_mutex_t leaving;

void cutHair() {
    printf("[BARBER] Haircut for customer %d started...\n", total_customer_count);
    // Picking a random haircut time.
    int time = rand() % haircut_time_bound + 1; // NOLINT
    // Waiting unlit haircut end.
    sleep(time);
    printf("[BARBER] Haircut for customer %d finished! \n\tTotal haircut time: %d.\n", total_customer_count, time);
    pthread_mutex_unlock(&cutting);
}

void getHaircut(int customer_index) {
    // Waiting until the haircut is finished.
    pthread_mutex_lock(&cutting);
    // Leaving the shop.
    printf("[CUSTOMER] Customer %d is leaving the shop... Bye!\n", customer_index);
    pthread_mutex_unlock(&leaving);
    // Unlocking cutting so that the next customer can get a haircut.
    pthread_mutex_unlock(&cutting);
}

void *barber(void *parameter) {
    while (total_customer_count < 10) {
        // Sleeping until a customer appears.
        sem_wait(&customers_waiting);

        // Waiting until modification is unlocked and locking it.
        pthread_mutex_lock(&incrementing);
        // Incrementing total visitor count, decrementing the number of people in the waiting room.
        waiting_room_customer_count--;
        total_customer_count++;
        printf("---------------------------------------\n");
        printf("[BARBER] Calling customer %d from the waiting room...\n\tTotal people in waiting room: %d\n",
               total_customer_count,
               waiting_room_customer_count);
        // Unlocking modification and making barber available.
        pthread_mutex_unlock(&incrementing);

        // Make the barber available.

        pthread_mutex_unlock(&busy);
        // Lock the cutting mutex and cut the customer's hair.
        pthread_mutex_lock(&cutting);

        cutHair();

        // Waiting until the customer is done.
        pthread_mutex_lock(&leaving);
    }
    return nullptr;
}

void *customer(void *parameter) {
    // Waiting until waiting room can be modified.
    pthread_mutex_lock(&incrementing);
    // Adding the current customer to the line.
    waiting_room_customer_count++;
    int current_index = ++new_customer_index;
    printf("[CUSTOMER] Customer %d entered the waiting room...\n\tTotal people in waiting room: %d\n",
           new_customer_index,
           waiting_room_customer_count);
    // Unlocking modification and incrementing waiting line.
    pthread_mutex_unlock(&incrementing);

    // Posting to the line (which indicates that there's a customer available).
    sem_post(&customers_waiting);

    // Waiting until the barber is available.
    pthread_mutex_lock(&busy);

    getHaircut(current_index);

    return nullptr;
}
