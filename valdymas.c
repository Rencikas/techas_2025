#include "valdymas.h"
#include "filtravimas.h"
#include "registration.h"
#include <stdio.h>
#include <string.h>

static void readString(const char *prompt, char *out, int max) {
    printf("%s", prompt);
    if (fgets(out, max, stdin)) {
        size_t l = strlen(out);
        if (l && out[l-1] == '\n') out[l-1] = '\0';
    } else {
        out[0] = '\0';
    }
}

void showFilterMenu(Car cars[], int count) {
    interactiveFilterMenu(cars, count);
}

void showValdymoMenu(Car cars[], int *count) {
    int ch = -1;
    while (ch != 0) {
        printf("-- Valdymo meniu --\n");
        printf("1. Atnaujinti TA data pagal valst.nr\n");
        printf("2. Redaguoti duomenis pagal valst.nr\n");
        printf("0. Grizti atgal\n");
        printf("Pasirinkimas: ");
        if (scanf("%d", &ch) != 1) { ch = 0; }
        getchar();
        if (ch == 1 || ch == 2) {
            char plate[MAX_STR];
            printf("Iveskite valstybini numeri: ");
            if (fgets(plate, sizeof(plate), stdin)) {
                size_t l = strlen(plate); if (l && plate[l-1] == '\n') plate[l-1] = '\0';
            }
            int idx = -1;
            for (int i = 0; i < *count; i++) {
                if (strcasecmp(cars[i].number, plate) == 0) { idx = i; break; }
            }
            if (idx == -1) { printf("Automobilis nerastas.\n"); continue; }
            if (ch == 1) {
                char date[MAX_STR];
                printf("Iveskite nauja TA data (YYYY-MM-DD arba -): ");
                if (fgets(date, sizeof(date), stdin)) { size_t l = strlen(date); if (l && date[l-1] == '\n') date[l-1] = '\0'; }
                strncpy(cars[idx].inspection_expiry, date, sizeof(cars[idx].inspection_expiry)-1);
                cars[idx].inspection_expiry[sizeof(cars[idx].inspection_expiry)-1] = '\0';
                if (!saveVehicles(cars, *count)) {
                    printf("Klaida irasant i duomenu baze (data/cars.txt)\n");
                } else {
                    printf("Atnaujinta ir issaugota:\n");
                }
                getVehicle(&cars[idx]);
            } else {
                char tmp[MAX_STR];
                printf("Marke (dabartine: %s): ", cars[idx].make); if (fgets(tmp, sizeof(tmp), stdin)) { size_t l = strlen(tmp); if (l && tmp[l-1] == '\n') tmp[l-1] = '\0'; }
                if (tmp[0] != '\0') strncpy(cars[idx].make, tmp, MAX_STR-1);
                printf("Spalva (dabartine: %s): ", cars[idx].color); if (fgets(tmp, sizeof(tmp), stdin)) { size_t l = strlen(tmp); if (l && tmp[l-1] == '\n') tmp[l-1] = '\0'; }
                if (tmp[0] != '\0') strncpy(cars[idx].color, tmp, MAX_STR-1);
                printf("Kuras (dabartinis: %s): ", cars[idx].fuel); if (fgets(tmp, sizeof(tmp), stdin)) { size_t l = strlen(tmp); if (l && tmp[l-1] == '\n') tmp[l-1] = '\0'; }
                if (tmp[0] != '\0') strncpy(cars[idx].fuel, tmp, MAX_STR-1);
                printf("Kategorija (dabartine: %s): ", cars[idx].category); if (fgets(tmp, sizeof(tmp), stdin)) { size_t l = strlen(tmp); if (l && tmp[l-1] == '\n') tmp[l-1] = '\0'; }
                if (tmp[0] != '\0') strncpy(cars[idx].category, tmp, MAX_STR-1);
                if (!saveVehicles(cars, *count)) {
                    printf("Klaida irasant i duomenu baze (data/cars.txt)\n");
                } else {
                    printf("Atnaujinta ir issaugota:\n");
                }
                getVehicle(&cars[idx]);
            }
        }
    }
}
