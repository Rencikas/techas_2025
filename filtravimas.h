#ifndef FILTRAVIMAS_H
#define FILTRAVIMAS_H

#include "car.h"

#define MAX_FILTERS 8

typedef struct {
    char field[MAX_STR];
    char value[MAX_STR];
} Filter;

int filterCars(const Car cars[], int count, const Filter filters[], int nfilters, int results[], int max_results);

void interactiveFilterMenu(Car cars[], int count);

#endif
