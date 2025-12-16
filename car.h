#ifndef CAR_H
#define CAR_H

#define MAX_STR 32

#include <time.h>

typedef struct {
    char number[MAX_STR];
    char make[MAX_STR];
    char color[MAX_STR];
    char fuel[MAX_STR];
    char category[MAX_STR];
    char reg_timestamp[20];
    char inspection_expiry[20];
} Car;
    
int loadVehicles(Car **cars, int *size);
int saveVehicles(Car *cars, int count);
int addVehicle(Car **cars, int *count, Car new_car);
void getVehicle(const Car *car);
void getVehicles(const Car *cars, int count, int limit);
int searchVehicles(const Car *cars, int count, const char *field, const char *value, int *results, int max_results);

#endif