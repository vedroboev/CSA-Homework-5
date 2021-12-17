// Definitions for the various barbershop methods and constants.
#include "barbershop.h"

//----------------------------------------------------------------------------------------------------------------------
// VARIABLES.
//----------------------------------------------------------------------------------------------------------------------

// Limit constants.
const int CUSTOMER_LIMIT = 50;
const int DAY_DURATION_LIMIT = 300;

// Max customer count and the upper limit to a haircut duration, day duration.
int daily_customer_count = 10;
// These are measured in seconds.
int haircut_time_bound = 10;
int day_duration = 120;

// Variables for keeping track of customers in the waiting room.
int total_customer_count = 0;
int waiting_room_customer_count = 0;
int new_customer_index = 0;

// Semaphore for the customers waiting in the waiting room.
sem_t customers_waiting;

// Mutex for modifying waiting room data.
pthread_mutex_t incrementing;
// Mutex for when the barber is cutting his hair.
pthread_mutex_t cutting;
// Mutex for when the barber is busy.
pthread_mutex_t busy;
// Mutex for when the customer is leaving the shop.
pthread_mutex_t leaving;

//----------------------------------------------------------------------------------------------------------------------
// INITIALIZERS, GENERATORS.
//----------------------------------------------------------------------------------------------------------------------

// Initializes semaphore and mutex variables.
void initializeSemaphores() {
    sem_init(&customers_waiting, 0, 0);
    pthread_mutex_init(&incrementing, nullptr);
    pthread_mutex_init(&cutting, nullptr);
    pthread_mutex_init(&busy, nullptr);
    pthread_mutex_init(&leaving, nullptr);
    // Leaving and busy need to be locked from the beginning.
    pthread_mutex_lock(&leaving);
    pthread_mutex_lock(&busy);
}

// Handles the creation and the generation of new customers throughout the day.
void generateCustomers() {
    pthread_t customers[CUSTOMER_LIMIT];

    // Getting the maximum wait time between new customers arriving.
    int wait_time = day_duration / daily_customer_count;
    if (wait_time == 0) ++wait_time;

    // Creating new customers with a random interval between them.
    for (int i = 0; i < daily_customer_count; ++i) {
        pthread_create(&customers[i], nullptr, customer, nullptr);
        sleep(rand() % wait_time); // NOLINT
    }
}

//----------------------------------------------------------------------------------------------------------------------
// UTILITY FUNCTIONS.
//----------------------------------------------------------------------------------------------------------------------

// Utility for working with cutting the customer's hair.
void cutHair() {
    printf("[BARBER] Haircut for customer %d started...\n", total_customer_count);
    // Picking a random haircut time.
    int time = rand() % haircut_time_bound + 1; // NOLINT
    // Waiting unlit haircut end.
    sleep(time);
    // Signalling the end of the haircut.
    printf("[BARBER] Haircut for customer %d finished! \n\tTotal haircut time: %d.\n", total_customer_count, time);
    pthread_mutex_unlock(&cutting);
}

// Utility for getting the hair cut + leaving the store.
void getHaircut(int customer_index) {
    // Waiting until the haircut is finished.
    pthread_mutex_lock(&cutting);
    // Leaving the shop.
    printf("[CUSTOMER] Customer %d is leaving the shop... Bye!\n", customer_index);
    pthread_mutex_unlock(&leaving);
    // Unlocking cutting so that the next customer can get a haircut.
    pthread_mutex_unlock(&cutting);
}

//----------------------------------------------------------------------------------------------------------------------
// MAIN HANDLER METHODS.
//----------------------------------------------------------------------------------------------------------------------

// Barber thread function.
void *barber(void *parameter) {
    time_t begin;
    time_t end;
    time(&begin);

    // Main body loop, doing this until the working day ends (we'll serve the latest customer even after closing).
    while (true) {
        // Sleeping until a customer appears.
        sem_wait(&customers_waiting);

        // Waiting until modification is unlocked and locking it.
        pthread_mutex_lock(&incrementing);
        // Incrementing total visitor count, decrementing the number of people in the waiting room.
        waiting_room_customer_count--;
        total_customer_count++;
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

        // Checking break condition.
        time(&end);
        if (difftime(end, begin) > day_duration || total_customer_count >= daily_customer_count) {
            break;
        }
    }
    printf("[BARBER] Working day has ended! Bye everyone!\n");
    return nullptr;
}

// Customer thread function.
void *customer(void *parameter) {
    // Waiting until waiting room can be modified.
    pthread_mutex_lock(&incrementing);
    // Adding the current customer to the line, getting the index of the current customer.
    waiting_room_customer_count++;
    int current_index = ++new_customer_index;
    printf("[WAITING ROOM] Customer %d entered the waiting room...\n\tTotal people in waiting room: %d\n",
           new_customer_index,
           waiting_room_customer_count);
    // Unlocking modification.
    pthread_mutex_unlock(&incrementing);

    // Posting to the line (which indicates that there's a customer available).
    sem_post(&customers_waiting);

    // Waiting until the barber is available.
    pthread_mutex_lock(&busy);

    // Getting the haircut (and leaving).
    getHaircut(current_index);

    return nullptr;
}
