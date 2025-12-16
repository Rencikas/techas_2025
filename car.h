#ifndef CAR_H
#define CAR_H

#define MAX_CARS 1000
#define MAX_STR 32

typedef struct {
    char number[MAX_STR];
    char make[MAX_STR];
    char color[MAX_STR];
    char fuel[MAX_STR];
    char category[MAX_STR];
} Car;

int load_cars(Car cars[], int max);
int save_cars(Car cars[], int count);
int add_car(Car cars[], int *count, Car new_car);
void print_car(const Car *car);
void print_cars(const Car cars[], int count, int limit);
int search_cars(const Car cars[], int count, const char *field, const char *value, int results[], int max_results);

#endif
