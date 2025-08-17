#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "shoppingcart.h"
#include "shoppingitem.h"

void* safeRealloc(void* base, size_t newByteCount) {
    void* temp = realloc(base, newByteCount);
    if (!temp)
        free(base);
    return temp;

}

void addProductToShoppingCart(ShoppingCart* sc, ShoppingItem* newItem) {

    if (sc == NULL || newItem == NULL) {
        return;
    }
    sc->shoppingItem = (ShoppingItem**)safeRealloc(sc->shoppingItem, (sc->NumOfQuantity + 1) * sizeof(ShoppingItem*));
    if (!sc->shoppingItem) {
        return;
    }
    sc->shoppingItem[sc->NumOfQuantity] = (ShoppingItem*)malloc(sizeof(ShoppingItem));
    if (!sc->shoppingItem[sc->NumOfQuantity]) {
        return;
    }

    *sc->shoppingItem[sc->NumOfQuantity] = *newItem;
    sc->NumOfQuantity++;
    printf("Product added to cart successfully\n");
}

float calcSumTotal(const ShoppingCart* sc) {
    int i;
    float totalPrice = 0;
    for (i = 0; i < sc->NumOfQuantity; i++) {
        totalPrice += sc->shoppingItem[i]->price * sc->shoppingItem[i]->quantity;
    }
    return totalPrice;
}
void printShoppingCart(ShoppingCart* sc)
{
    int i;
    if (sc->NumOfQuantity == 0)
    {
        printf("Shopping cart is empty!\n");
        return;
    }
    for (i = 0; i < sc->NumOfQuantity; i++)
    {
        printf("Item %s count %d price per item %.2f\n", sc->shoppingItem[i]->barcode, sc->shoppingItem[i]->quantity, sc->shoppingItem[i]->price);
    }
    printf("Total bill to pay: %.2f\n", calcSumTotal(sc));
}

void freeShoppingCart(ShoppingCart* sc) {
    int i;
    if (sc == NULL) {
        return;
    }
    if (sc->shoppingItem != NULL) {
        for (i = 0; i < sc->NumOfQuantity; i++) {
            if (sc->shoppingItem[i] != NULL) {
                free(sc->shoppingItem[i]);
            }
        }
        free(sc->shoppingItem);
    }
    free(sc);
}








