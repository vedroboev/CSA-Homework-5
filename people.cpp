
#include "people.h"

void *Barber::cutHair(Customer customer) {
    std::cout << "Cutting hair of customer "  << customer.name << "...";
    return nullptr;
}
void *Customer::enterShop() {
    std::cout << "Customer "  << name << " entering shop...";
    return nullptr;
}
void *Customer::getHairCut() {
    std::cout << "Customer " << name << " is getting his hair cut...";
    return nullptr;
}
void *Customer::leaveShop() {
    std::cout << "Customer " << name << " is leaving the shop...";
    return nullptr;
}
