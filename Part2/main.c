#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "SuperMarket.h"
#include "Product.h"

int main()
{
    SuperMarket market;

    srand((unsigned int)time(NULL));

    if (!initSuperMarket(&market)) {
        printf("Error initializing Super Market\n");
        return 0;
    }

    int option;
    int stop = 0;
    int sortFlag = 0;

    do {
        option = menu();

        switch (option) {
            case eShowSuperMarket:
                printSuperMarket(&market);
                break;

            case eAddProduct:
                if (!addProduct(&market))
                    printf("Error adding product\n");
                else
                    printf("Product added successfully!\n");
                break;

            case eAddCustomer:
                if (!addCustomer(&market))
                    printf("Error adding customer\n");
                else
                    printf("Customer added successfully!\n");
                break;

            case eCustomerDoShopping:
                if (!doShopping(&market))
                    printf("Error in shopping\n");
                break;

            case ePrintCart:
                doPrintCart(&market);
                break;

            case eCustomerManageShoppingCart:
                if (!manageShoppingCart(&market))
                    printf("Error in shopping cart management\n");
                break;

            case eSortProducts: {
                int choice;
                printf("Sort products by:\n1. Name\n2. Quantity\n3. Price\n");
                scanf("%d", &choice);

                sortFlag = sortProducts(&market, choice);
                if (sortFlag == 0)
                    printf("Error in sorting the products\n");
                else
                    printf("Products sorted successfully!\n");
                break;
            }

            case eFindBinarySearch:
                if (sortFlag != 1 && sortFlag != 2 && sortFlag != 3) {
                    printf("Cannot search, list isn't sorted\n");
                    break;
                }

                Product* bProduct = binarySearch(&market, sortFlag);
                if (!bProduct)
                    printf("Item was not found\n");
                else {
                    printf("Item was found:\n");
                    printProduct(&bProduct);
                }
                break;

            case ePrintProductByType:
                printProductByType(&market);
                break;

            case EXIT:
                printf("Bye bye\n");
                stop = 1;
                break;

            default:
                printf("Wrong option\n");
                break;
        }
    } while (!stop);

    freeMarket(&market);

    return 0;
}

int menu()
{
    int option;
    char c;

    while (1) {
        printf("\nPlease choose one of the following options:\n");
        for (int i = 0; i < eNofOptions; i++)
            printf("%d - %s\n", i, menuStrings[i]);
        printf("%d - Quit\n", EXIT);

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");

            while ((c = getchar()) != '\n' && c != EOF);

            continue;
        }

        while ((c = getchar()) != '\n' && c != EOF);

        if ((option >= 0 && option <= 8) || option == EXIT) {
            return option;
        } else {
            printf("Invalid option. Please choose a valid number.\n");
        }
    }
}


