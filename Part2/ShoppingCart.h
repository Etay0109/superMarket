#pragma once
#include "ShoppingItem.h"
#include "list.h"

typedef struct
{
	LIST Item;
}ShoppingCart;


void			initCart(ShoppingCart* pCart);
float			getTotalPrice(const ShoppingCart* pCart);
ShoppingItem*	getItemByBarocde(ShoppingCart* pCart, const char* barcode);
int				L_sortByBarcode(NODE* head, ShoppingItem* newItem);
int				addItemToCart(ShoppingCart* pCart, const char* name, float price, int count);
float			printShoppingCart(const ShoppingCart* pCart, float discount);
void			freeShoppingCart(ShoppingCart* pCart);
