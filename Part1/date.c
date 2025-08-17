#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "date.h"
#include <string.h>


int stringToInt(char* str, int size) {
    int result = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        result = result * 10 + (str[i] - '0');
    }
    return result;
}
void date_init(Date* date) {
    char date1[9] = { 0 };
    int fContinue = 1;
    do {
        printf("Please enter date \"DDMMYYYY\" format \n");
        scanf("%8s", date1);
        if (strlen(date1) != 8) {
            printf("Invalid format please enter exactly 8 digits \n");
            continue;
        }
        date->day = stringToInt(date1, 2);
        date->month = stringToInt(date1 + 2, 2);
        date->year = stringToInt(date1 + 4, 4);
        if (date->day == -1 || date->month == -1 || date->year == -1) {
            printf("Invalid date format, please enter numbers only\n");
            continue;
        }

        if (valid_date(date->year, date->month, date->day)) {
            fContinue = 0;
        }
        else {
            printf("Invalid date, please try again\n");
        }
    } while (fContinue);
}

int valid_date(int year, int month, int day) {
    if (year < 2024 || year > 2030)
        return 0;
    if (month < 1 || month > 12)
        return 0;
    if (day <= 0 || day > 31)
        return 0;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return 0;
    }
    else if (month == 2) {
        if (day > 28)
            return 0;
    }
    return 1;
}

void printDate(Date* d)
{
    printf("%02d/%02d/%04d\n", d->day, d->month, d->year);
}





