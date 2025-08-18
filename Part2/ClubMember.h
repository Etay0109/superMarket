#pragma once
#include "Customer.h"

typedef struct ClubMember
{
	Customer base;
	int totalMonth;
} ClubMember;

void initClubMember(struct Customer* pCustomer);
void initClubMemberVTable(struct Customer* pCustomer);
void printClubMember(struct Customer* pCustomer);
void freeClubMember(struct Customer* pCustomer);
float calculateDiscount(struct Customer* pCustomer);
