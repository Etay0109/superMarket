#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "shoppingitem.h"
#include "product.h"

void shoppingItem_init(ShoppingItem* si) {
    if (si == NULL) {
        printf("ERROR: Null pointer passed to shoppingItem_init\n");
        return;
    }
    for (int i = 0; i < BARCODENUM; i++) {
        si->barcode[i] = '\0';
    }
    si->price = 0;
    si->quantity = 0;
}




