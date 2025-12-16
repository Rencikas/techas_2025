#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "car.h"

#define INSPECTION_INTERVALS_FILE "data/inspection_intervals.txt"

// Kuro tipo indeksai ir jų pavadinimai
static const char *FUEL_TYPES[] = {
    [1] = "Benzinas",
    [2] = "Dyzelinas",
    [3] = "Elektra",
    [4] = "Benzinas/Dujos"
};

// Tikrina ar valstybiniai numeriai yra galiojancio formato
int isValidPlate(const char *plate) {
    if (!plate || !*plate) return 0;
    
    for (const char *p = plate; *p; p++) {
        if (isdigit((unsigned char)*p)) return 1;
    }
    return 0;
}

// Tikrina ar masinos pavadinimas yra galiojancio formato
int isValidMake(const char *make) {
    return make && *make;
}

// Tikrina ar masinos spalva yra galiojancio formato
int isValidColor(const char *color) {
    return color && *color;
}

// Tikrina ar kuro tipas yra galiojancio formato
int isValidFuel(int choice) {
    return choice >= 1 && choice <= 4;
}

// Tikrina ar kategorija yra galiojancio formato
int isValidCategory(const char *category) {
    if (!category || !*category) return 0;

    FILE *f = fopen(INSPECTION_INTERVALS_FILE, "r");
    if (!f) return 0;

    char cat[32];
    int val, found = 0;

    while (fscanf(f, "%31s %d", cat, &val) == 2) {
        if (strcmp(cat, category) == 0) {
            found = 1;
            break;
        }
    }

    fclose(f);
    return found;
}

static void newLine(char *str) {
    char *nl = strchr(str, '\n');
    if (nl) *nl = '\0';
}

static void readLine(const char *prompt, char *buf, size_t size, int (*validate)(const char *), const char *error_msg) {
    do {
        printf("%s", prompt);
        if (!fgets(buf, size, stdin)) continue;
        newLine(buf);
        
        if (!validate(buf)) {
            printf("%s\n", error_msg);
        }
    } while (!validate(buf));
}

static int getInspectionInterval(const char *category) {
    FILE *f = fopen(INSPECTION_INTERVALS_FILE, "r");
    if (!f) return 1;

    char cat[32];
    int val, interval = 1;

    while (fscanf(f, "%31s %d", cat, &val) == 2) {
        if (strcmp(cat, category) == 0) {
            interval = val;
            break;
        }
    }

    fclose(f);
    return interval;
}

static int findCarByPlate(Car cars[], int count, const char *plate) {
    for (int i = 0; i < count; i++) {
        if (strcmp(cars[i].number, plate) == 0) return i;
    }
    return -1;
}

int registerVehicle(Car cars[], int *car_count) {
    Car new_car;

    readLine("\nValstybiniai numeriai: ", new_car.number, sizeof(new_car.number), isValidPlate, "Numeriuose turi buti bent vienas skaicius ir negali buti tuscias!");
    readLine("Pilnas masinos pavadinimas: ", new_car.make, sizeof(new_car.make), isValidMake, "Pavadinimas negali buti tuscias!");
    readLine("Spalva: ", new_car.color, sizeof(new_car.color), isValidColor, "Spalva negali buti tuscia!");

    // Kuro pasirinkimas
    int fuelType = 0;
    do {
        printf("Kuro tipas:\n"
               "1 - Benzinas\n"
               "2 - Dyzelinas\n"
               "3 - Elektra\n"
               "4 - Benzinas/Dujos\n"
               "Pasirinkite kuro tipa (1-4): ");

        char input[16];
        if (!fgets(input, sizeof(input), stdin) || sscanf(input, "%d", &fuelType) != 1 || !isValidFuel(fuelType)) {
            printf("Netinkamas pasirinkimas!\n");
            fuelType = 0;
        }
    } while (!isValidFuel(fuelType));

    strcpy(new_car.fuel, FUEL_TYPES[fuelType]);
    readLine("Kategorija: ", new_car.category, sizeof(new_car.category), isValidCategory, "Netinkama kategorija!");

    // Nustatome registracijos ir technines apziuros datas
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(new_car.reg_timestamp, sizeof(new_car.reg_timestamp), "%Y-%m-%d", t);

    struct tm expiry = *t;
    expiry.tm_year += getInspectionInterval(new_car.category);
    mktime(&expiry);
    strftime(new_car.inspection_expiry, sizeof(new_car.inspection_expiry), "%Y-%m-%d", &expiry);

    // Saugome arba atnaujiname automobili
    int index = findCarByPlate(cars, *car_count, new_car.number);
    
    if (index >= 0) {
        cars[index] = new_car;
        saveVehicles(cars, *car_count);
        printf("Automobilio duomenys atnaujinti!\n");
    } else if (addVehicle(cars, car_count, new_car)) {
        saveVehicles(cars, *car_count);
        printf("Automobilis uzregistruotas!\n");
    } else {
        printf("Nepavyko uzregistruoti (duomenu bazes limitas)!\n");
    }

    return 0;
}