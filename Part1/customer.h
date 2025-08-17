#pragma once
#include "shoppingcart.h"
#define MAXID 10

typedef struct{
    char id[MAXID];
    char* name;
    ShoppingCart* shoppingCart;
}Customer;

char* myGets(char* buffer, int size);
void trimWhiteSpace(char* str);
void formatName(char* str);
void initCustomer(Customer* c);
void initShoppingCart(Customer* c);
void initId(Customer* c);
Customer* addCustomer(Customer** customers);
void freeCustomer(Customer* c);

