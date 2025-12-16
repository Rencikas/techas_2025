#include "filtravimas.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

static int matchFilter(const Car *car, const Filter *f) {
    if (f->value == NULL || f->value[0] == '\0') return 1;

    char lhs[MAX_STR];
    char rhs[MAX_STR];
    const char *fieldVal = NULL;
    if (strcmp(f->field, "numeris") == 0) fieldVal = car->number;
    else if (strcmp(f->field, "marke") == 0) fieldVal = car->make;
    else if (strcmp(f->field, "spalva") == 0) fieldVal = car->color;
    else if (strcmp(f->field, "kuras") == 0) fieldVal = car->fuel;
    else if (strcmp(f->field, "kategorija") == 0) fieldVal = car->category;
    else if (strcmp(f->field, "apziura") == 0) {
        if (f->value[0] == '\0') return 1;
        for (int i = 0; f->value[i] && i < MAX_STR-1; i++) rhs[i] = tolower((unsigned char)f->value[i]);
        rhs[strlen(f->value)] = '\0';

        if (strcmp(rhs, "tanera") == 0) {
            if (car->inspection_expiry[0] == '-' || car->inspection_expiry[0] == '\0') return 1;
            struct tm tm = {0};
            int y, m, d;
            if (sscanf(car->inspection_expiry, "%d-%d-%d", &y, &m, &d) == 3) {
                int ey = y, em = m, ed = d;
                time_t now = time(NULL);
                struct tm *nowtm = localtime(&now);
                int cy = nowtm->tm_year + 1900;
                int cm = nowtm->tm_mon + 1;
                int cd = nowtm->tm_mday;
                if (ey < cy || (ey == cy && (em < cm || (em == cm && ed < cd)))) return 1;
                if (car->reg_timestamp[0] != '\0' && car->reg_timestamp[0] != '-') {
                    int ry, rm, rd;
                    if (sscanf(car->reg_timestamp, "%d-%d-%d", &ry, &rm, &rd) == 3) {
                        if (ey < ry || (ey == ry && (em < rm || (em == rm && ed < rd)))) return 1;
                    }
                }
                return 0;
            }
            return 0;
        } else if (strcmp(rhs, "tayra") == 0) {
            if (car->inspection_expiry[0] == '-' || car->inspection_expiry[0] == '\0') return 0;
            struct tm tm = {0};
            int y, m, d;
            if (sscanf(car->inspection_expiry, "%d-%d-%d", &y, &m, &d) == 3) {
                int ey = y, em = m, ed = d;
                time_t now = time(NULL);
                struct tm *nowtm = localtime(&now);
                int cy = nowtm->tm_year + 1900;
                int cm = nowtm->tm_mon + 1;
                int cd = nowtm->tm_mday;
                if (ey > cy || (ey == cy && (em > cm || (em == cm && ed >= cd)))) {
                    if (car->reg_timestamp[0] != '\0' && car->reg_timestamp[0] != '-') {
                        int ry, rm, rd;
                        if (sscanf(car->reg_timestamp, "%d-%d-%d", &ry, &rm, &rd) == 3) {
                            if (ey < ry || (ey == ry && (em < rm || (em == rm && ed < rd)))) return 0;
                        }
                    }
                    return 1;
                }
                return 0;
            }
            return 0;
        } else {
            fieldVal = car->inspection_expiry;
        }
    } else {
        return 0;
    }

    if (fieldVal == NULL) return 0;
    size_t i;
    for (i = 0; i < MAX_STR-1 && fieldVal[i]; i++) lhs[i] = tolower((unsigned char)fieldVal[i]); lhs[i] = '\0';
    for (i = 0; i < MAX_STR-1 && f->value[i]; i++) rhs[i] = tolower((unsigned char)f->value[i]); rhs[i] = '\0';

    if (strstr(lhs, rhs) != NULL) return 1;
    return 0;
}

int filterCars(const Car *cars, int count, const Filter *filters, int nfilters, int *results, int max_results) {
    int found = 0;
    for (int i = 0; i < count && found < max_results; i++) {
        int ok = 1;
        for (int f = 0; f < nfilters; f++) {
            if (filters[f].field[0] == '\0') continue;
            if (!matchFilter(&cars[i], &filters[f])) { ok = 0; break; }
        }
        if (ok) results[found++] = i;
    }
    return found;
}

static void trim_newline(char *s) {
    size_t l = strlen(s);
    if (l > 0 && s[l-1] == '\n') s[l-1] = '\0';
}

void interactiveFilterMenu(Car *cars, int count) {
    Filter filters[3];
    for (int i = 0; i < 3; i++) { filters[i].field[0] = '\0'; filters[i].value[0] = '\0'; }
    int nfilters = 0;

    char buf[64];
    printf("Filtravimo pasirinkimai: \n1. TA galioja \n2. TA negalioja \n0. Testi nepriklausomai\nPasirinkti: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) return;
    int ta_choice = atoi(buf);
    if (ta_choice == 1) {
        strncpy(filters[nfilters].field, "apziura", MAX_STR-1);
        strncpy(filters[nfilters].value, "tayra", MAX_STR-1);
        nfilters++;
    } else if (ta_choice == 2) {
        strncpy(filters[nfilters].field, "apziura", MAX_STR-1);
        strncpy(filters[nfilters].value, "tanera", MAX_STR-1);
        nfilters++;
    }

    printf("Galima filtruoti pagal: \nMarke \nSpalva \nKura \nKategorija\n");
    printf("Kiek papildomu filtru naudoti (0-2)? ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) return;
    int add = atoi(buf);
    if (add < 0) add = 0; if (add > 2) add = 2;

    for (int i = 0; i < add && nfilters < 3; i++) {
        char field[MAX_STR];
        char value[MAX_STR];
        printf("Pasirinkti ir irasyti #%d (marke | spalva | kuras | kategorija): ", i+1);
        if (fgets(field, sizeof(field), stdin) == NULL) break; trim_newline(field);
        printf("Reiksme #%d: ", i+1);
        if (fgets(value, sizeof(value), stdin) == NULL) break; trim_newline(value);
        if (strcmp(field, "marke") != 0 && strcmp(field, "spalva") != 0 && strcmp(field, "kuras") != 0 && strcmp(field, "kategorija") != 0) {
            printf("Neteisingas laukas: %s - praleidziame\n", field);
            continue;
        }
        strncpy(filters[nfilters].field, field, MAX_STR-1);
        strncpy(filters[nfilters].value, value, MAX_STR-1);
        nfilters++;
    }

    int *results = count > 0 ? malloc(count * sizeof(int)) : NULL;
    int found = 0;
    if (results) found = filterCars(cars, count, filters, nfilters, results, count);
    
    if (!results || found == 0) {
        printf("Nerasta atitikmenu.\n");
        if (results) free(results);
        return;
    }
    printf("Rasta %d irasu:\n", found);
    for (int i = 0; i < found; i++) {
        getVehicle(&cars[results[i]]);
    }
    free(results);
}
