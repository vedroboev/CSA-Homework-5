#include "barbershop.h"

int main() {
    // Getting data from user.
    printf("Welcome to the barbershop simulator!\n");
    printf("Please, enter the working day duration in seconds:\n");
    while (scanf("%d", &day_duration) != 1 || day_duration <= 10 || day_duration >= DAY_DURATION_LIMIT) { // NOLINT
        printf("Error: day duration must be a number and must be in range 10, %d. Try again:\n", DAY_DURATION_LIMIT);
    }

    printf("Please, enter the number of customers on the current day:\n");
    while (scanf("%d", &daily_customer_count) != 1 || daily_customer_count < 1 // NOLINT
        || daily_customer_count >= CUSTOMER_LIMIT) { // NOLINT
        printf("Error: customer count must be a number and must be in range 1, %d. Try again:\n", CUSTOMER_LIMIT);
    }

    printf("Please, enter the average duration of the haircut:\n");
    while (scanf("%d", &haircut_time_bound) != 1 || haircut_time_bound <= 0 // NOLINT
        || haircut_time_bound >= day_duration) { // NOLINT
        printf("Haircut duration must be a positive number and be less that the length of the day. Try again:\n");
    }

    // Initializing all variables.
    initializeSemaphores();

    // Creating a barber.
    pthread_t barbershop;
    pthread_create(&barbershop, nullptr, barber, nullptr);

    // Creating customers.
    generateCustomers();

    // Waiting untill the barber has finished working.
    pthread_join(barbershop, nullptr);

    return 0;
}
