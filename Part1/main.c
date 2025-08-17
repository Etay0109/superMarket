#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "supermarket.h"

int main() {
    SuperMarket sm;
    int fContinue = 1;
    int option;
    supermarket_init(&sm);
    do {
        printf("Please choose one of the following option\n");
        printf(" 0 - Show SuperMarket\n");
        printf(" 1 - Add product\n");
        printf(" 2 - Add customer\n");
        printf(" 3 - Customer shopping\n");
        printf(" 4 - Print shopping cart\n");
        printf(" 5 - Customer Shopping Cart Managment\n");
        printf(" 6 - Print product by type\n");
        printf(" -1 - Quit\n");
        scanf("%d", &option);
        getchar();

        switch(option) {
            case 0:
                printf("Super Market Name : %s\n", sm.name);
            printf("There are %d products\n", sm.numOfProducts);
            printSuperMarket(&sm);
            printf("There are %d listed customers \n", sm.numOfCustomers);
            break;
            case 1:
                addProductToSuperMarket(&sm);
            break;
            case 2:
                addCustomerToSuperMarket(&sm);
            break;
            case 3:
                buyingProcess(&sm);
            break;
            case 4:
                printCustomerDetails(&sm);
            break;
            case 5:
                shoppingCartManagment(&sm);
            break;
            case 6:
                printProductByType(&sm);
            break;
            case -1:
                printf("bye bye\n");
            freeSuperMarket(&sm);
            fContinue = 0;
            break;
            default:
                printf("Wrong option\n");

        }
    } while (fContinue);
    return 0;

}