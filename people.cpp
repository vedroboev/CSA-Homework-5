
#include "people.h"

void *Barber::cutHair(Customer customer) {
    printf("Cutting hair of customer %s...", customer.name);
    sleep(1);
    return nullptr;
}
void *Customer::enterShop() {
    printf("Customer %s entering shop...", name);
    return nullptr;
}
void *Customer::getHairCut() {
    printf("Customer %s is getting his hair cut...", name);
    return nullptr;
}
void *Customer::leaveShop() {
    printf("Customer %s is leaving the shop...", name);
    return nullptr;
}
