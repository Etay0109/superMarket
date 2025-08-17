#pragma once
#include "customer.h"
#include "product.h"
#define MAXSIZE 255

typedef struct{
    char name[MAXSIZE];
    Customer** customersArr;
    int numOfCustomers;
    Product** productsArr;
    int numOfProducts;
}SuperMarket;

void supermarket_init(SuperMarket* sm);
void printSuperMarket(SuperMarket* sm);
int printCustomerDetails(SuperMarket* sm);
int addProductToSuperMarket(SuperMarket* sm);
int findProductIndex(SuperMarket* sm, const char* barcode); // return the index of the product in arr product, else -1
int addCustomerToSuperMarket(SuperMarket* sm);
int findIdIndex(SuperMarket* sm, const char* id); //return the index of the id in arr customer, else -1
void buyingProcess(SuperMarket* sm);
int validBarcode(SuperMarket* sm, const char* barcode);
int isUniqueBarcode(SuperMarket* sm, const char* barcode); // check if the barcode is unique
void shoppingCartManagment(SuperMarket* sm);
void printProductByType(SuperMarket* sm);
void displayAllProducts(SuperMarket* sm);
void freeSuperMarket(SuperMarket* sm);


