#pragma once

typedef struct{
    int day;
    int month;
    int year;
} Date;

int stringToInt(char* str, int size);
void date_init(Date* d);
int valid_date(int year, int month, int day);
void printDate(Date* d);


