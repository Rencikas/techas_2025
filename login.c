#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "login.h"

#define USERS_FILE "data/users.txt"

void encrypt(char *text) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base + 2) % 26 + base;
        }
    }
}

void decrypt(char *text) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base - 2 + 26) % 26 + base;
        }
    }
}

void sign_up() {
    char user[50], pass1[50], pass2[50];

    printf("Username: ");
    scanf("%s", user);
    printf("-------------------------\n");
    printf("Password: ");
    scanf("%s", pass1);
    printf("-------------------------\n");
    printf("Repeat password: ");
    scanf("%s", pass2);
    printf("-------------------------\n");

    if (strcmp(pass1, pass2) != 0) {
        printf("Slaptazodziai nesutampa.\n");
        return;
    }

    encrypt(user);
    encrypt(pass1);

    FILE *f = fopen(USERS_FILE, "a");
    fprintf(f, "%s %s USER\n", user, pass1);
    fclose(f);

    printf("Registracija sekminga.\n");
}

int log_in(Session *session) {
    char user[50], pass[50];
    char f_user[50], f_pass[50], f_role[10];

    printf("Username: ");
    scanf("%s", user);
    printf("-------------------------\n");
    printf("Password: ");
    scanf("%s", pass);
    printf("-------------------------\n");

    encrypt(user);
    encrypt(pass);

    FILE *f = fopen(USERS_FILE, "r");
    if (!f) return 0;

    while (fscanf(f, "%s %s %s", f_user, f_pass, f_role) != EOF) {
        if (strcmp(user, f_user) == 0 && strcmp(pass, f_pass) == 0) {
            decrypt(f_user);
            strcpy(session->username, f_user);
            strcpy(session->role, f_role);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int login_menu(Session *session) {
    int choice;

    do {
        printf("\n1. Sign Up\n");
        printf("2. Log In\n");
        printf("0. Exit\n");
        printf("Pasirinkti: ");
        scanf("%d", &choice);

        if (choice == 1) sign_up();
        else if (choice == 2) {
            if (log_in(session)) return 1;
            printf("Neteisingi duomenys.\n");
        }
    } while (choice != 0);

    return 0;
}
