#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "customer.h"

char* myGets(char* buffer, int size)
{
    char* ok;
    if (buffer != NULL && size > 0) {
        do {
            ok = fgets(buffer, size, stdin);
        } while (ok && ((strlen(buffer) <= 1) && (iscntrl(buffer[0]))));
        if (ok)
        {
            char* back = buffer + strlen(buffer);
            while ((buffer < back) && iscntrl(*--back));
            *(back + 1) = '\0';
            return buffer;
        }

        buffer[0] = '\0';
    }
    return NULL;
}
void trimWhiteSpace(char* str) {
    int noSpace = 1;
    char* pLook = str;
    char* pWrite = str;

    while (*pLook)
    {
        if (*pLook != ' ')
        {
            *pWrite = *pLook;
            pWrite++;
            noSpace = 1;
        }
        else if ((*pLook == ' ') && (noSpace)) {
            *pWrite = *pLook;
            pWrite++;
            noSpace = 0;
        }
        pLook++;
    }
    *pWrite = '\0';
}
void formatName(char* str) {
    int i;
    trimWhiteSpace(str);
    if (strlen(str) == 0) {
        return;
    }
    if (isalpha(str[0])) {
        str[0] = toupper(str[0]);
    }
    size_t size = strlen(str);
    for (i = 1; i < size; i++) {
        str[i] = tolower(str[i]);
    }
}

void initCustomer(Customer* c) {
    c->id[MAXID - 1] = '\0';
    c->name = NULL;
    c->shoppingCart = NULL;
}

void initShoppingCart(Customer* c) {
    c->shoppingCart = (ShoppingCart*)malloc(sizeof(ShoppingCart));
    if (!c->shoppingCart)
        return;
    c->shoppingCart->NumOfQuantity = 0;
    c->shoppingCart->shoppingItem = NULL;
}


void initId(Customer* c) {
    char tempId[MAXID];
    int fContinue = 1;
    int i, length;
    do {
        printf("Id should be 9 digits \n For example : 123456789\n");
        myGets(tempId, MAXID);
        length = strlen(tempId);
        if (length != 9)
        {
            printf("Invalid id please try again");

        }
        else
        {
            for (i = 0; i < length; i++) {
                if (tempId[i] < '0' || tempId[i] > '9') {
                    break;
                }
            }
            strcpy(c->id, tempId);
            fContinue = 0;
        }

    } while (fContinue);

}

Customer* addCustomer(Customer** customers) {
    Customer* c = (Customer*)malloc(sizeof(Customer));
    if (c == NULL)
    {
        printf("ERROR memory allocation \n");
        exit(1);
    }
    char firstname[255];
    char lastname[255];
    printf("Enter customer first name\n");
    myGets(firstname, sizeof(firstname));
    printf("Enter customer last name\n");
    myGets(lastname, sizeof(lastname));
    formatName(firstname);
    formatName(lastname);
    size_t size = strlen(firstname) + strlen(lastname) + strlen(" - ") + 1;
    c->name = (char*)malloc(size);
    if (!c->name) {
        free(c);
        return NULL;
    }
    snprintf(c->name, size, "%s - %s", firstname, lastname);
    initId(c);
    initShoppingCart(c);
    return c;
}
void freeCustomer(Customer* c)
{
    if (c == NULL) {
        return;
    }
    if (c->name != NULL) {
        free(c->name);
    }
    if (c->shoppingCart != NULL) {
        free(c->shoppingCart);
    }
    free(c);
}

