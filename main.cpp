#include "barbershop.h"

int main() {
    sem_init(&customers_waiting, 0, 0);
    pthread_mutex_init(&incrementing, nullptr);
    pthread_mutex_init(&cutting, nullptr);
    pthread_mutex_init(&busy, nullptr);
    pthread_mutex_init(&leaving, nullptr);
    pthread_mutex_lock(&leaving);
    pthread_mutex_lock(&busy);

    // Creating customers.
    pthread_t customers[3];

    for (unsigned long & i : customers) {
        pthread_create(&i, nullptr, customer, nullptr);
    }

    barber(nullptr);

    return 0;
}
