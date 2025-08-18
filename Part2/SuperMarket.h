#pragma once
#include "Customer.h"
#include "Product.h"
#include "ShoppingCart.h"

typedef struct
{
    char*       name;
    Customer*   customerArr;
    int         customerCount;
    Product**   productArr;
    int         productCount;
} SuperMarket;

int     initSuperMarket(SuperMarket* pMarket);
void    printSuperMarket(const SuperMarket* pMarket);

int     addProduct(SuperMarket* pMarket);
int     addNewProduct(SuperMarket* pMarket);
int     isBarcodeUnique(const SuperMarket* pMarket, const char* barcode);
int     getProductIndexByBarcode(SuperMarket* pMarket, const char* barcode);
Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode);
Product* getProductFromUser(SuperMarket* pMarket, char* barcode);
void    getUniquBarcode(char* barcode, SuperMarket* pMarket);
void    printProductByType(SuperMarket* pMarket);
int     sortProducts(SuperMarket* pMarket, int field);
int     compareByName(const void* a, const void* b);
int     compareByQuantity(const void* a, const void* b);
int     compareByPrice(const void* a, const void* b);
Product* binarySearch(SuperMarket* pMarket, int flag);

int     addCustomer(SuperMarket* pMarket);
int     isCustomerInMarket(SuperMarket* pMarket, Customer* pCust);
int     isCustomerIdUnique(const SuperMarket* pMarket, const char* id);
Customer* FindCustomerById(SuperMarket* pMarket, const char* id);

int     doShopping(SuperMarket* pMarket);
Customer* doPrintCart(SuperMarket* pMarket);
int     manageShoppingCart(SuperMarket* pMarket);
Customer* getCustomerShopPay(SuperMarket* pMarket);
Customer* getCustomerWhoShop(SuperMarket* pMarket);
Product* getProductAndCount(SuperMarket* pMarket, int* pCount);
void    fillCart(SuperMarket* pMarket, ShoppingCart* pCart);
void    clearCart(SuperMarket* pMarket, Customer* pCustomer);

void    generalArrayFunction(void* array, int count, size_t elementSize, void (*f)(void* element));
void    printAllProducts(const SuperMarket* pMarket);
void    printAllCustomers(const SuperMarket* pMarket);

void    freeMarket(SuperMarket* pMarket);
void    freeProducts(SuperMarket* pMarket);
void    freeCustomers(SuperMarket* pMarket);
