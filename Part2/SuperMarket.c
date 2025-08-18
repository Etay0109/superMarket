#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "SuperMarket.h"
#include "Product.h"
#include "Customer.h"
#include "ShoppingCart.h"
#include "General.h"

int initSuperMarket(SuperMarket* pMarket) {
    pMarket->customerCount = 0;
    pMarket->customerArr = NULL;
    pMarket->productCount = 0;
    pMarket->productArr = NULL;
    pMarket->name = getStrExactLength("Enter market name");
    return pMarket->name != NULL;
}

void printSuperMarket(const SuperMarket* pMarket) {
    printf("Super Market Name: %s\n", pMarket->name);
    printAllProducts(pMarket);
    printAllCustomers(pMarket);
}

int addProduct(SuperMarket* pMarket) {
    char answer;
    char barcode[BARCODE_LENGTH + 1];
    Product* pProd = NULL;

    printf("\nAdding new product? y/Y: ");
    scanf(" %c", &answer);
    getchar();

    if (toupper(answer) == 'Y') {
        return addNewProduct(pMarket);
    } if (pMarket->productCount > 0) {
        printf("Do you want to increase the amount of an existing product? y/Y: ");
        scanf(" %c", &answer);
        getchar();
        if (toupper(answer) == 'Y') {
            printAllProducts(pMarket);
            pProd = getProductFromUser(pMarket, barcode);
            if (pProd) updateProductCount(pProd);
        }
    } else return 0;

    return 1;
}

int addNewProduct(SuperMarket* pMarket) {
    Product** pTempArr = (Product**)realloc(pMarket->productArr, (pMarket->productCount + 1) * sizeof(Product*));
    if (!pTempArr) { freeProducts(pMarket); return 0; }
    pMarket->productArr = pTempArr;

    Product* pProd = (Product*)calloc(1, sizeof(Product));
    if (!pProd) { free(pMarket->productArr); return 0; }

    initProductNoBarcode(pProd);
    do { generateBarcode(pProd); } while (!isBarcodeUnique(pMarket, pProd->barcode));

    pMarket->productArr[pMarket->productCount] = pProd;
    pMarket->productCount++;
    printf("Product '%s' with barcode '%s' added successfully!\n", pProd->name, pProd->barcode);
    return 1;
}

int isBarcodeUnique(const SuperMarket* pMarket, const char* barcode) {
    for (int i = 0; i < pMarket->productCount; i++)
        if (strcmp(pMarket->productArr[i]->barcode, barcode) == 0)
            return 0;
    return 1;
}

int isCustomerIdUnique(const SuperMarket* pMarket, const char* id) {
    for (int i = 0; i < pMarket->customerCount; i++)
        if (strcmp(pMarket->customerArr[i].id, id) == 0)
            return 0;
    return 1;
}

int addCustomer(SuperMarket* pMarket) {
    Customer cust = {0};
    do {
        freeCustomer(&cust);
        initCustomer(&cust);
    } while (!isCustomerIdUnique(pMarket, cust.id));

    pMarket->customerArr = (Customer*)safeRealloc(pMarket->customerArr, (pMarket->customerCount + 1) * sizeof(Customer));
    if (!pMarket->customerArr) { free(cust.name); return 0; }

    pMarket->customerArr[pMarket->customerCount] = cust;
    pMarket->customerCount++;
    printf("Customer '%s' with ID '%s' added successfully!\n", cust.name, cust.id);
    return 1;
}

int isCustomerInMarket(SuperMarket* pMarket, Customer* pCust) {
    for (int i = 0; i < pMarket->customerCount; i++)
        if (strcmp(pMarket->customerArr[i].name, pCust->name) == 0)
            return 1;
    return 0;
}

int doShopping(SuperMarket* pMarket) {
    Customer* pCustomer = getCustomerShopPay(pMarket);
    if (!pCustomer) return 0;

    if (!pCustomer->pCart) {
        pCustomer->pCart = (ShoppingCart*)malloc(sizeof(ShoppingCart));
        if (!pCustomer->pCart) return 0;
        initCart(pCustomer->pCart);
    }

    fillCart(pMarket, pCustomer->pCart);

    if (pCustomer->pCart->Item.head.next == NULL) {
        free(pCustomer->pCart);
        pCustomer->pCart = NULL;
    }

    printf("---------- Shopping ended ----------\n");
    return 1;
}

Customer* doPrintCart(SuperMarket* pMarket) {
    Customer* pCustomer = getCustomerShopPay(pMarket);
    if (!pCustomer) return NULL;
    if (!pCustomer->pCart) {
        printf("Customer cart is empty\n");
        return NULL;
    }
    printShoppingCart(pCustomer->pCart, pCustomer->vTable.discount(pCustomer));
    return pCustomer;
}

int manageShoppingCart(SuperMarket* pMarket) {
    Customer* pCustomer = doPrintCart(pMarket);
    if (!pCustomer) return 0;

    char answer;
    printf("Do you want to pay for the cart? y/Y, anything else to cancel shopping!\t");
    do { scanf(" %c", &answer); } while (isspace(answer));
    getchar();

    if (answer == 'y' || answer == 'Y') pay(pCustomer);
    else {
        clearCart(pMarket, pCustomer);
        cancelShopping(pCustomer);
    }
    return 1;
}

Customer* getCustomerShopPay(SuperMarket* pMarket) {
    if (pMarket->customerCount == 0) { printf("No customer listed to market\n"); return NULL; }
    if (pMarket->productCount == 0) { printf("No products in market - cannot shop\n"); return NULL; }
    Customer* pCustomer = getCustomerWhoShop(pMarket);
    if (!pCustomer) { printf("This customer is not listed\n"); return NULL; }
    return pCustomer;
}

void generalArrayFunction(void* array, int count, size_t elementSize, void (*f)(void* element)) {
    for (int i = 0; i < count; i++) {
        void* element = (char*)array + i * elementSize;
        f(element);
    }
}

void printAllProducts(const SuperMarket* pMarket) {
    printf("There are %d products\n", pMarket->productCount);
    printf("%-20s %-10s %-20s %-10s %-20s %-15s\n", "Name", "Barcode", "Type", "Price", "Count In Stock", "Expiry Date");
    printf("-------------------------------------------------------------------------------\n");
    generalArrayFunction(pMarket->productArr, pMarket->productCount, sizeof(Product*), printProduct);
}

void printAllCustomers(const SuperMarket* pMarket) {
    printf("There are %d listed customers\n", pMarket->customerCount);
    for (int i = 0; i < pMarket->customerCount; i++)
        pMarket->customerArr[i].vTable.print(&pMarket->customerArr[i]);
}

Customer* getCustomerWhoShop(SuperMarket* pMarket) {
    printAllCustomers(pMarket);
    char searchTerm[MAX_STR_LEN];
    getsStrFixSize(searchTerm, sizeof(searchTerm), "Who is shopping? Enter customer id\n");
    return FindCustomerById(pMarket, searchTerm);
}

Product* getProductAndCount(SuperMarket* pMarket, int* pCount) {
    char barcode[BARCODE_LENGTH + 1];
    Product* pProd = getProductFromUser(pMarket, barcode);
    if (!pProd) { printf("No such product\n"); return NULL; }
    if (pProd->count == 0) { printf("This product is out of stock\n"); return NULL; }

    int count;
    do {
        printf("How many items do you want? max %d\n", pProd->count);
        scanf("%d", &count);
    } while (count <= 0 || count > pProd->count);

    *pCount = count;
    return pProd;
}

void fillCart(SuperMarket* pMarket, ShoppingCart* pCart) {
    printAllProducts(pMarket);
    char op;
    while (1) {
        printf("Do you want to shop for a product? y/Y, anything else to exit!!\t");
        do { scanf(" %c", &op); } while (isspace(op));
        getchar();

        if (op != 'y' && op != 'Y') break;

        int count;
        Product* pProd = getProductAndCount(pMarket, &count);
        if (pProd) {
            if (!addItemToCart(pCart, pProd->barcode, pProd->price, count)) {
                printf("Error adding item\n");
                return;
            }
            pProd->count -= count;
        }
    }
}

void clearCart(SuperMarket* pMarket, Customer* pCustomer) {
    if (!pCustomer->pCart) return;
    NODE* current = pCustomer->pCart->Item.head.next;
    while (current) {
        ShoppingItem* pItem = (ShoppingItem*)current->key;
        Product* p = getProductByBarcode(pMarket, pItem->barcode);
        if (p) p->count += pItem->count;
        current = current->next;
    }
}

void freeMarket(SuperMarket* pMarket) {
    free(pMarket->name);
    freeProducts(pMarket);
    freeCustomers(pMarket);
}

void freeProducts(SuperMarket* pMarket) {
    for (int i = 0; i < pMarket->productCount; i++) {
        freeProduct(pMarket->productArr[i]);
        free(pMarket->productArr[i]);
    }
    free(pMarket->productArr);
}

void freeCustomers(SuperMarket* pMarket) {
    for (int i = 0; i < pMarket->customerCount; i++)
        freeCustomer(&pMarket->customerArr[i]);
    free(pMarket->customerArr);
}


// Find customer by ID
Customer* FindCustomerById(SuperMarket* pMarket, const char* id) {
    for (int i = 0; i < pMarket->customerCount; i++)
        if (strcmp(pMarket->customerArr[i].id, id) == 0)
            return &pMarket->customerArr[i];
    return NULL;
}

// Get product by barcode
Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode) {
    for (int i = 0; i < pMarket->productCount; i++)
        if (strcmp(pMarket->productArr[i]->barcode, barcode) == 0)
            return pMarket->productArr[i];
    return NULL;
}

// Get product from user input (asks barcode)
Product* getProductFromUser(SuperMarket* pMarket, char* barcode) {
    printf("Enter product barcode: ");
    scanf("%s", barcode);
    return getProductByBarcode(pMarket, barcode);
}


// Sort Products
int sortProducts(SuperMarket* pMarket, int field)
{
    switch (field) {
        case 1: // Name
            qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareByName);
        return 1;
        case 2: // Quantity
            qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareByQuantity);
        return 2;
        case 3: // Price
            qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareByPrice);
        return 3;
        default:
            return 0;
    }
}


int compareByName(const void* a, const void* b) {
    Product* pa = *(Product**)a;
    Product* pb = *(Product**)b;
    return strcmp(pa->name, pb->name);
}

int compareByQuantity(const void* a, const void* b) {
    Product* pa = *(Product**)a;
    Product* pb = *(Product**)b;
    return pa->count - pb->count;
}

int compareByPrice(const void* a, const void* b) {
    Product* pa = *(Product**)a;
    Product* pb = *(Product**)b;
    if (pa->price < pb->price) return -1;
    if (pa->price > pb->price) return 1;
    return 0;
}

// Binary Search
Product* binarySearch(SuperMarket* pMarket, int flag) {
    if (pMarket == NULL || pMarket->productCount == 0)
        return NULL;

    if (flag == 1) { // Name
        char search[MAX_STR_LEN];
        getsStrFixSize(search, sizeof(search), "Enter product name to search: ");

        Product key;
        strcpy(key.name, search);
        Product* keyPtr = &key;

        Product** res = (Product**)bsearch(&keyPtr,
                                           pMarket->productArr,
                                           pMarket->productCount,
                                           sizeof(Product*),
                                           compareByName);
        return res ? *res : NULL;

    } else if (flag == 2) { // Quantity
        int value;
        printf("Enter quantity to search: ");
        if (scanf("%d", &value) != 1)
            return NULL;

        Product key;
        key.count = value;
        Product* keyPtr = &key;

        Product** res = (Product**)bsearch(&keyPtr,
                                           pMarket->productArr,
                                           pMarket->productCount,
                                           sizeof(Product*),
                                           compareByQuantity);
        return res ? *res : NULL;

    } else if (flag == 3) { // Price
        float value;
        printf("Enter price to search: ");
        if (scanf("%f", &value) != 1)
            return NULL;

        Product key;
        key.price = value;
        Product* keyPtr = &key;

        Product** res = (Product**)bsearch(&keyPtr,
                                           pMarket->productArr,
                                           pMarket->productCount,
                                           sizeof(Product*),
                                           compareByPrice);
        return res ? *res : NULL;
    }

    return NULL;
}




// Print Product by Type
void printProductByType(SuperMarket* pMarket) {
    int type;
    printf("Enter product type (0=FruitVeg,1=Fridge,2=Frozen,3=Shelf): ");
    scanf("%d", &type);
    for (int i = 0; i < pMarket->productCount; i++)
        if (pMarket->productArr[i]->type == type)
            printProduct(&pMarket->productArr[i]);
}


