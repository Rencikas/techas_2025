#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"

#define USERS_FILE "data/users.txt"

void decrypt(char *text);

void admin_panel() {
    char users[100][3][50];
    int count = 0, choice;

    FILE *f = fopen(USERS_FILE, "r");
    while (fscanf(f, "%s %s %s",
           users[count][0],
           users[count][1],
           users[count][2]) != EOF) {
        decrypt(users[count][0]);
        count++;
    }
    fclose(f);

    do {
        printf("\n-------------------------------\n");
        printf("0. Exit\n");
        for (int i = 0; i < count; i++)
            printf("%d. %s %s\n", i + 1, users[i][0], users[i][2]);
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
            if (opt == 2) strcpy(users[choice - 1][2], "ADMIN");

            f = fopen(USERS_FILE, "w");
            for (int i = 0; i < count; i++)
                fprintf(f, "%s %s %s\n",
                        users[i][0], users[i][1], users[i][2]);
            fclose(f);
        }

    } while (choice != 0);
}
