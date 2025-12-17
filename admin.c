#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"

#define USERS_FILE "data/users.txt"
#define MAX_USERS 100
#define MAX_LEN 50

void decrypt(char *text);

void admin_panel() {
    char users[MAX_USERS][3][MAX_LEN];
    char display_users[MAX_USERS][MAX_LEN];
    int count = 0, choice;

    FILE *f = fopen(USERS_FILE, "r");
    if (!f) {
        printf("Nepavyko atidaryti users failo.\n");
        return;
    }

    while (count < MAX_USERS &&
           fscanf(f, "%s %s %s",
                  users[count][0],
                  users[count][1],
                  users[count][2]) != EOF) {

        strcpy(display_users[count], users[count][0]);
        decrypt(display_users[count]);
        count++;
    }
    fclose(f);

    do {
        printf("\n-------------------------------\n");
        printf("0. Exit\n");
        for (int i = 0; i < count; i++)
            printf("%d. %s %s\n", i + 1, display_users[i], users[i][2]);
        printf("-------------------------------\n");
        printf("Pasirinkti: ");
        scanf("%d", &choice);

        if (choice > 0 && choice <= count) {
            int opt;
            printf("1. Make User\n");
            printf("2. Make Admin\n");
            printf("0. Exit\n");
            scanf("%d", &opt);

            if (opt == 1) strcpy(users[choice - 1][2], "USER");
            else if (opt == 2) strcpy(users[choice - 1][2], "ADMIN");

            f = fopen(USERS_FILE, "w");
            if (!f) {
                printf("Nepavyko atidaryti users failo rasymui.\n");
                return;
            }

            for (int i = 0; i < count; i++) {
                fprintf(f, "%s %s %s\n",
                        users[i][0],
                        users[i][1],
                        users[i][2]);
            }
            fclose(f);

            printf("Role atnaujinta sekmingai.\n");
        }

    } while (choice != 0);
}
