#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "supermarket.h"
#include "shoppingcart.h"
#include "product.h"
#include "customer.h"

void supermarket_init(SuperMarket* sm) {
    puts("Enter market name");
    myGets(sm->name, MAXSIZE);
    sm->numOfCustomers = 0;
    sm->customersArr = NULL;
    sm->numOfProducts = 0;
    sm->productsArr = NULL;
}

int printCustomerDetails(SuperMarket* sm) {
    if (sm == NULL || sm->customersArr == NULL || sm->numOfCustomers == 0) {
        printf("No customers in the supermarket.\n");
        return -1;
    }

    int i, index;
    char id[MAXID];
    printf("There are %d listed customers\n", sm->numOfCustomers);
    for (i = 0; i < sm->numOfCustomers; i++) {
        printf("Name : %s\n", sm->customersArr[i]->name);
        printf("ID : %s\n", sm->customersArr[i]->id);
    }

    printf("Who is shopping? enter customer id\n");
    myGets(id, MAXID);
    index = findIdIndex(sm, id);
    if (index != -1) {
        printShoppingCart(sm->customersArr[index]->shoppingCart);
        return index;
    } else {
        return -1;
    }
}

void printSuperMarket(SuperMarket* sm) {
    printf("-----------------------------------------------------------------------------------------\n");
    printf("No.  Name               Expiry Date   Barcode      Type             Price      Quantity\n");
    printf("-----------------------------------------------------------------------------------------\n");
    displayAllProducts(sm);
}

int findProductIndex(SuperMarket* sm, const char* barcode) {
    if (sm == NULL || barcode == NULL) {
        return -1;
    }
    for (int i = 0; i < sm->numOfProducts; i++) {
        if (sm->productsArr[i] != NULL && sm->productsArr[i]->barcode[0] != '\0'
            && strcmp(sm->productsArr[i]->barcode, barcode) == 0) {
            return i;
        }
    }
    return -1;
}

void displayAllProducts(SuperMarket* sm) {
    for (int i = 0; i < sm->numOfProducts; i++) {
        printProduct(sm->productsArr[i], i + 1);
        printf("\n");
    }
}

int addProductToSuperMarket(SuperMarket* sm) {
    sm->productsArr = (Product**)safeRealloc(sm->productsArr, (sm->numOfProducts + 1) * sizeof(Product*));
    if (!sm->productsArr) return 0;

    sm->productsArr[sm->numOfProducts] = addProduct(&sm->productsArr[sm->numOfProducts]);
    if (sm->productsArr[sm->numOfProducts] == NULL) return 0;

    if (isUniqueBarcode(sm, sm->productsArr[sm->numOfProducts]->barcode)) {
        printf("is unique barcode\n");
    }

    sm->numOfProducts++;
    printf("Product added to store successfully.\n");
    return 1;
}

int findIdIndex(SuperMarket* sm, const char* id) {
    if (sm == NULL || id == NULL) return -1;

    for (int i = 0; i < sm->numOfCustomers; i++) {
        if (sm->customersArr[i] != NULL && sm->customersArr[i]->id[0] != '\0'
            && strcmp(sm->customersArr[i]->id, id) == 0) {
            return i;
        }
    }
    return -1;
}

int addCustomerToSuperMarket(SuperMarket* sm) {
    sm->customersArr = (Customer**)safeRealloc(sm->customersArr, (sm->numOfCustomers + 1) * sizeof(Customer*));
    if (!sm->customersArr) return 0;

    sm->customersArr[sm->numOfCustomers] = addCustomer(&sm->customersArr[sm->numOfCustomers]);
    if (sm->customersArr[sm->numOfCustomers] == NULL) return 0;

    if (findIdIndex(sm, sm->customersArr[sm->numOfCustomers]->id) != -1) {
        printf("This customer already exists\n");
        return 0;
    }

    sm->numOfCustomers++;
    printf("Customer added to store successfully.\n");
    return 1;
}

int validBarcode(SuperMarket* sm, const char* barcode) {
    if (barcode == NULL || strlen(barcode) != BARCODENUM - 1) {
        printf("Invalid barcode length\n");
        return 0;
    }

    for (int i = 0; i < sm->numOfProducts; i++) {
        if (strncmp(sm->productsArr[i]->barcode, barcode, 2) != 0) {
            continue;
        } else {
            for (int j = 2; j < BARCODENUM; j++) {
                if (sm->productsArr[i]->barcode[j] != barcode[j]) {
                    printf("No such barcode\nNo such product\n");
                    return 0;
                }
            }
            return 1;
        }
    }

    printf("Invalid type prefix\n");
    return 0;
}

void buyingProcess(SuperMarket* sm) {
    if (sm->numOfCustomers == 0) {
        printf("No customer listed in market \nError in shopping \n");
        return;
    }

    char id[MAXID], barcode[BARCODENUM], choice;
    int amount, productIndex, customerIndex;

    printf("Who is shopping? enter customer id\n");
    myGets(id, MAXID);
    customerIndex = findIdIndex(sm, id);
    if (customerIndex == -1) {
        printf("This customer is not listed\nError in shopping\n");
        return;
    }

    printSuperMarket(sm);
    printf("Do you want to shop for a product? Y/y, anything else to exit\n");
    scanf(" %c", &choice);
    do {
        if (tolower(choice) != 'y') return;

        printf("Code should be of 7 length exactly\nMust have 2 type prefix letters followed by a 5 digit number\n");
        printf("For example: FR20301\n");
        myGets(barcode, BARCODENUM);

        if (!validBarcode(sm, barcode)) continue;

        productIndex = findProductIndex(sm, barcode);
        if (productIndex == -1) {
            printf("This product is not in our stock\n");
            continue;
        }

        Product* selectedProduct = sm->productsArr[productIndex];
        printf("How many items do you want? Max %d\n", selectedProduct->quantity);
        scanf("%d", &amount);

        if (amount <= 0 || amount > selectedProduct->quantity) {
            printf("Error: can't add this quantity\n");
            continue;
        }

        ShoppingItem newItem;
        shoppingItem_init(&newItem);
        strcpy(newItem.barcode, barcode);
        newItem.price = selectedProduct->price;
        newItem.quantity = amount;
        addProductToShoppingCart(sm->customersArr[customerIndex]->shoppingCart, &newItem);

        selectedProduct->quantity -= amount;
        printf("Do you want to shop for a product? Y/y, anything else to exit\n");
        scanf(" %c", &choice);
    } while (tolower(choice) == 'y');
}

int isUniqueBarcode(SuperMarket* sm, const char* barcode) {
    if (barcode == NULL || strlen(barcode) == 0) return 0;

    for (int i = 0; i < sm->numOfProducts; i++) {
        if (strcmp(sm->productsArr[i]->barcode, barcode) == 0) return 0;
    }
    return 1;
}

void shoppingCartManagment(SuperMarket* sm) {
    char choice;
    int index = printCustomerDetails(sm);
    if (index == -1) {
        printf("Error in customer management\n");
        return;
    }

    printf("Do you want to pay for the cart? Y, anything else to cancel shopping \n");
    scanf(" %c", &choice);

    if (tolower(choice) == 'y') {
        printf("---------- Cart info and bill for %s ----------\n", sm->customersArr[index]->name);
        printShoppingCart(sm->customersArr[index]->shoppingCart);
        printf("!!! --- Payment was received ----\n");
        initShoppingCart(sm->customersArr[index]);
    }
}

void printProductByType(SuperMarket* sm) {
    int productByType;
    printf("Please enter one of the following types: \n0 for Shelf\n1 for Frozen\n2 for Fridge\n3 for Fruit Vegetable\n");
    scanf("%d", &productByType);

    printf("-----------------------------------------------------------------------------------------\n");
    printf("No.  Name               Expiry Date   Barcode      Type             Price      Quantity\n");
    printf("-----------------------------------------------------------------------------------------\n");

    int j = 1;
    for (int i = 0; i < sm->numOfProducts; i++) {
        if (sm->productsArr[i]->productType == productByType) {
            printProduct(sm->productsArr[i], j++);
            printf("\n");
        }
    }
}

void freeSuperMarket(SuperMarket* sm) {
    if (!sm) return;

    for (int i = 0; i < sm->numOfCustomers; i++) {
        if (sm->customersArr[i] != NULL) freeCustomer(sm->customersArr[i]);
    }
    free(sm->customersArr);

    for (int i = 0; i < sm->numOfProducts; i++) {
        if (sm->productsArr[i] != NULL) freeProduct(sm->productsArr[i]);
    }
    free(sm->productsArr);
}

