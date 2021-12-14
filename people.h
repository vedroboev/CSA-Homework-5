#ifndef CSA_HOMEWORK_5__PEOPLE_H_
#define CSA_HOMEWORK_5__PEOPLE_H_

#include "stdio.h"  // NOLINT(modernize-deprecated-headers)
#include "unistd.h"

class Customer {
public:
    char name[256];
    void *enterShop();
    void *getHairCut();
    void *leaveShop();
};

class Barber {
public:
    void *cutHair(Customer customer);
};

#endif //CSA_HOMEWORK_5__PEOPLE_H_
