#pragma once
#include "shoppingitem.h"
typedef struct{
    ShoppingItem** shoppingItem;
    int NumOfQuantity;
}ShoppingCart;

void* safeRealloc(void* base, size_t newByteCount);
void printShoppingCart(ShoppingCart* sc);
void freeShoppingCart(ShoppingCart* sc);
float calcSumTotal(const ShoppingCart* sc);
void addProductToShoppingCart(ShoppingCart* sc, ShoppingItem* newItem);



