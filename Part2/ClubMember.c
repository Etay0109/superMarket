#include <stdio.h>
#include <stdlib.h>
#include "ClubMember.h"
#include "Customer.h"

void initClubMember(struct Customer* pCustomer)
{
	if (pCustomer == NULL)
		return;

	if (pCustomer->vTable.init)
		pCustomer->vTable.init(pCustomer);

	pCustomer->pDerivedObj = malloc(sizeof(ClubMember));
	if (!pCustomer->pDerivedObj)
		return;

	ClubMember* clubMember = (ClubMember*)pCustomer->pDerivedObj;
	printf("Enter months of membership: ");
	scanf("%d", &clubMember->totalMonth);

	initClubMemberVTable(pCustomer);
}

void initClubMemberVTable(struct Customer* pCustomer)
{
	pCustomer->vTable.init = initClubMember;
	pCustomer->vTable.print = printClubMember;
	pCustomer->vTable.freedata = freeClubMember;
	pCustomer->vTable.discount = calculateDiscount;
}

void printClubMember(struct Customer* pCustomer)
{
	printCustomer(pCustomer);
	ClubMember* clubMember = (ClubMember*)pCustomer->pDerivedObj;
	printf("Months of membership: %d\n", clubMember->totalMonth);
}

float calculateDiscount(struct Customer* pCustomer)
{
	ClubMember* clubMember = (ClubMember*)pCustomer->pDerivedObj;
	if (clubMember->totalMonth < 24)
		return 0.001f * clubMember->totalMonth;
	else if (clubMember->totalMonth < 60)
		return 0.025f + 0.005f * (clubMember->totalMonth / 12);
	else
		return 0.075f;
}

void freeClubMember(struct Customer* pCustomer)
{
	if (pCustomer->pDerivedObj)
		free(pCustomer->pDerivedObj);

	freeCustomer(pCustomer);
}
