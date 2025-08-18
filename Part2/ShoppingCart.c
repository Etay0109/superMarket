#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ShoppingCart.h"
#include "list.h"

void initCart(ShoppingCart* pCart)
{
	L_init(&pCart->Item);
}

float	getTotalPrice(const ShoppingCart* pCart)
{
	float price = 0;
	NODE* pItem = pCart->Item.head.next;
	while (pItem != NULL)
	{
		ShoppingItem* item = (ShoppingItem*)pItem->key;
		price += (item->price * item->count);
		pItem = pItem->next;
	}
	return price;
}
int L_sortByBarcode(NODE* head, ShoppingItem* newItem)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if (!newNode)
		return 0;
	newNode->key = newItem;
	newNode->next = NULL;

	if (!head->next || strcmp(newItem->barcode, ((ShoppingItem*)head->next->key)->barcode) < 0)
	{
		newNode->next = head->next;
		head->next = newNode;
		return 1;
	}
	NODE* current = head->next;
	while (current->next && strcmp(newItem->barcode, ((ShoppingItem*)current->next->key)->barcode) > 0)
	{
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
	return 1;
}

int		addItemToCart(ShoppingCart* pCart, const char* barcode, float price, int count)
{
	ShoppingItem* pItemexists = getItemByBarocde(pCart, barcode);
	if (pItemexists)
		pItemexists->count += count;//new item
	else{
		ShoppingItem* newItem = createItem(barcode, price, count);
		if (!newItem)
			return 0;
		if(!L_sortByBarcode(&pCart->Item.head, newItem))
		{
			free(newItem);
			return 0;
		}
	}
	return 1;
}

float printShoppingCart(const ShoppingCart* pCart, float discount)
{
	NODE* current = pCart->Item.head.next;
	float price = 0;

	L_print(&pCart->Item, (void(*)(const void*))printItem);

	while (current)
	{
		ShoppingItem* item = (ShoppingItem*)current->key;
		price += item->price * item->count;
		current = current->next;
	}

	printf("Total bill to pay: %.2f\n", price - (price * discount));
	return price;
}



ShoppingItem* getItemByBarocde(ShoppingCart* pCart, const char* barcode)
{
	NODE* current = pCart->Item.head.next;
	while (current != NULL) {
		ShoppingItem* pItem = (ShoppingItem*)current->key;
		if (strcmp(pItem->barcode, barcode) == 0)
			return pItem;
		current = current->next;
	}
	return NULL;
}

void	freeShoppingCart(ShoppingCart* pCart)
{
	NODE* current = pCart->Item.head.next;
	while (current) {
		ShoppingItem* pItem = (ShoppingItem*)current->key;
		free(pItem);
		current = current->next;
	}
	L_free(&pCart->Item);
}
