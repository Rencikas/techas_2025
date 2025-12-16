#include "car.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadVehicles(Car **cars, int *size) {
    FILE *f = fopen("data/cars.txt", "r");
    if (!f) {
        *cars = NULL;
        *size = 0;
        return 0;
    }
    int capacity = 16;
    int count = 0;
    Car *arr = malloc(capacity * sizeof(Car));
    if (!arr) {
        fclose(f);
        *cars = NULL;
        *size = 0;
        return 0;
    }
    while (1) {
        if (count >= capacity) {
            capacity *= 2;
            Car *tmp = realloc(arr, capacity * sizeof(Car));
            if (!tmp) break;
            arr = tmp;
        }
        Car temp;
        int res = fscanf(f, "%31[^,],%31[^,],%31[^,],%31[^,],%31[^,],%19[^,],%19[^\n]\n", temp.number, temp.make, temp.color, temp.fuel, temp.category, temp.reg_timestamp, temp.inspection_expiry);
        if (res != 7) break;
        if (strlen(temp.reg_timestamp) == 0) strcpy(temp.reg_timestamp, "-");
        if (strlen(temp.inspection_expiry) == 0) strcpy(temp.inspection_expiry, "-");
        arr[count++] = temp;
    }
    fclose(f);
    *cars = arr;
    *size = count;
    return count;
}

int saveVehicles(Car *cars, int count) {
    FILE *f = fopen("data/cars.txt", "w");
    if (!f) return 0;
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s,%s,%s,%s,%s,%s,%s\n", cars[i].number, cars[i].make, cars[i].color, cars[i].fuel, cars[i].category, cars[i].reg_timestamp, cars[i].inspection_expiry);
    }
    fclose(f);
    return 1;
}

int addVehicle(Car **cars, int *count, Car new_car) {
    Car *tmp = realloc(*cars, (*count + 1) * sizeof(Car));
    if (!tmp) return 0;
    *cars = tmp;
    (*cars)[*count] = new_car;
    (*count)++;
    return 1;
}

void getVehicle(const Car *car) {
    printf("Nr: %s | Marke: %s | Spalva: %s | Kuras: %s | Kategorija: %s | Registruota: %s | TA galioja iki: %s\n", car->number, car->make, car->color, car->fuel, car->category, car->reg_timestamp, car->inspection_expiry);
}

void getVehicles(const Car *cars, int count, int limit) {
    int to_print = (limit > 0 && limit < count) ? limit : count;
    for (int i = 0; i < to_print; i++) {
        getVehicle(&cars[i]);
    }
}

int searchVehicles(const Car *cars, int count, const char *field, const char *value, int *results, int max_results) {
    int found = 0;
    for (int i = 0; i < count && found < max_results; i++) {
        if ((strcmp(field, "number") == 0 && strcmp(cars[i].number, value) == 0) ||
            (strcmp(field, "make") == 0 && strcmp(cars[i].make, value) == 0) ||
            (strcmp(field, "color") == 0 && strcmp(cars[i].color, value) == 0) ||
            (strcmp(field, "fuel") == 0 && strcmp(cars[i].fuel, value) == 0) ||
            (strcmp(field, "category") == 0 && strcmp(cars[i].category, value) == 0)) {
            results[found++] = i;
        }
    }
    return found;
}
