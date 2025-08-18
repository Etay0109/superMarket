#pragma once
#include "ShoppingCart.h"
#include "vTable.h"

#define CUSTOMER_ID_LENGTH 9
#define NAMES_SEP " "
#define NAME_PARTS_SEP "- "

typedef struct Customer
{
	char*			id;
	char*			name;
	ShoppingCart*	pCart;
	void* pDerivedObj;
	customerVTable vTable;
}Customer;

void	initCustomer(Customer* pCustomer);
void	initCustomervTable(Customer* pCustomer);
float	customerDiscount(Customer* pCustomer);
void	getCustomerID(Customer* pCustomer);
void	printCustomer(Customer* pCustomer);

int		isCustomerIdValid(const char* id);
int		isCustomerById(const Customer* pCust, const char* id);
void	getNamePart(char* part, const char* msg);
void	upperLowerCustomerName(char* name);
char*	combineFirstLast(char** parts);
void	pay(Customer* pCustomer);
void	cancelShopping(Customer* pCustomer);
void	freeCustomer(Customer* pCust);




