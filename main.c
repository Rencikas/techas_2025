#include <stdio.h>
#include <string.h>
#include "login.h"
#include "admin.h"

int main() {
    Session session;

    if (!login_menu(&session)) {
        printf("Programa baigta.\n");
        return 0;
    }

    int choice;
    do {
        printf("\n-------------------------\n");
        printf("1. Auto registravimas\n");
        printf("2. Duomenu baze\n");
        printf("3. Filtravimo sistema\n");
        printf("4. Valdymas\n");

        if (strcmp(session.role, "ADMIN") == 0)
            printf("5. Admin panel\n");

        printf("0. Exit\n");
        printf("-------------------------\n");
        printf("Pasirinkti: ");
        scanf("%d", &choice);

        if (choice == 5 && strcmp(session.role, "ADMIN") == 0)
            admin_panel();

    } while (choice != 0);

    printf("Programa baigta.\n");
    return 0;
}
