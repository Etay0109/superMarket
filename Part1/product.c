#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "customer.h"
#include "date.h"


int randomDigit() {
    return rand() % 10;

}
void barcodeMaker(Product* p, const char ch1[], int size) {
    int i;
    if (p == NULL || ch1 == NULL) {
        return;
    }
    p->barcode[0] = ch1[0];
    p->barcode[1] = ch1[1];
    for (i = 2; i < BARCODENUM - 1; i++) {
        p->barcode[i] = '0' + randomDigit();
    }
    p->barcode[BARCODENUM - 1] = '\0';
}
int validNum(float num) {
    return num >= 0;
}
Product* addProduct(Product** products){
    Product* p = malloc(sizeof(Product));
    if (p == NULL)
    {
        printf("ERROR memory allocation \n");
        exit(1);
    }
    printf("enter product name up to 20 chars\n");
    myGets(p->name, MAXNAME);
    int fContinue = 1;
    do {
        printf("please enter one of the following types: \n 0 for Shelf \n 1 for Frozen \n 2 for Fridge \n 3 for Fruit Vegetable\n");
        scanf("%d", &p->productType);
        if (p->productType >= 0 && p->productType < eNofProducts) {
            barcodeMaker(p, ProductTypeStrings[p->productType], strlen(ProductTypeStrings[p->productType]));
            fContinue = 0;
        }

        else {
            printf("Invalid option please try again !\n");
        }
    } while (fContinue);
    p->expireDate = (Date*)malloc(sizeof(Date));
    if (!p->expireDate)
        return NULL;
    date_init(p->expireDate);
    do {
        printf("Enter product price: \n");
        scanf("%f", &p->price);
        if (!validNum(p->price)) {
            printf("Invalid price!\n ");
        }
    } while (!validNum(p->price));
    do {
        printf("Enter product number of items\n");
        scanf("%d", &p->quantity);
        if (p->quantity <= 0) {
            printf("Error\n");
        }

    } while (p->quantity < 0);
    return p;

}

void printProduct(Product* p, int productNumber) {
    printf("%-5d %-20s %02d/%02d/%04d %-12s %-15s %-10.2f %-10d\n",
        productNumber,
        p->name,
        p->expireDate->day,
        p->expireDate->month,
        p->expireDate->year,
        p->barcode,
        ProductTypeStrings[(int)p->productType],
        p->price,
        p->quantity);
}


void freeProduct(Product* p) {
    if (p == NULL) {
        return;
    }
    if (p->expireDate != NULL) {
        free(p->expireDate);
    }
    free(p);
}







