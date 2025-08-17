#pragma once
#define MAXNAME 20
#define BARCODENUM 8
#include "date.h"

typedef enum { eShelf, eFrozen, eFridge, eFruitVegetable, eNofProducts, eOther } ProductType;
static const char* ProductTypeStrings[eNofProducts] = { "SH", "FZ", "FR", "FV" };

typedef struct{
    char name[MAXNAME];
    char barcode[BARCODENUM];
    ProductType productType;
    float price;
    int quantity;
    Date* expireDate;
} Product;

int randomDigit();
int validNum(float num);
void barcodeMaker(Product* p, const char ch1[], int size);
void printProduct(Product* p, int productNumber);
Product* addProduct(Product** products);
void freeProduct(Product* p);


