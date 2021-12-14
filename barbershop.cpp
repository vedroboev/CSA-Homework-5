#include "stdio.h" // NOLINT(modernize-deprecated-headers)

#include "barbershop.h"
Barbershop::Barbershop(int average_cutting_time) {
    this->average_cutting_time = average_cutting_time;
    this->total_customer_count = 0;
    this->waiting_room_count = 0;
    pthread_mutex_init(&incrementing, nullptr);
    pthread_mutex_init(&cutting, nullptr);
    sem_init(&customers_waiting, 0, 0);
}
void *Barbershop::barber() {
    while (total_customer_count < 100){
        // Sleeping until a customer appears.
        sem_wait(&customers_waiting);

        // Waiting until modification is unlocked and locking it.
        pthread_mutex_lock(&incrementing);
        // Incrementing total visitor count, decrementing the number of people in the waiting room.
        waiting_room_count--;
        total_customer_count++;
        // Unlocking modification and making barber available.

        pthread_mutex_unlock(&incrementing);
        pthread_mutex_unlock(&cutting);
        // Cutting the customer's hair.
    }
}
void *Barbershop::customer() {
    while (total_customer_count < 100){
        // Waiting until waiting room can be modified.
        pthread_mutex_lock(&incrementing);
        // Adding the current customer to the line.
        waiting_room_count++;
        // Unlocking modification and incrementing waiting line.
        pthread_mutex_unlock(&incrementing);
        sem_post(&customers_waiting);
        // Waiting until the barber is available.
        pthread_mutex_lock(&cutting);
        // Getting the haircut.
        getHaircut();
    }
}

void Barbershop::getHaircut() {
    printf("Haircut for customer %d started...", total_customer_count);
    // Picking a random haircut time.
    int time = rand() % 10 + 1;
    // Waiting unlit haircut end.
    sleep(time);
    printf("Haircut for customer %d finished! Total time: %d.", total_customer_count, time);
}
