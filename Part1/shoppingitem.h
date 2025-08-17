#pragma once
#include "product.h"

typedef struct{
    char barcode[BARCODENUM];
    float price;
    int quantity;

}ShoppingItem;

void shoppingItem_init(ShoppingItem* si);


