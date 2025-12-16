#include <stdio.h>
#include <string.h>
#include "login.h"
#include "admin.h"
#include "car.h"
#include "registration.h"

int main() {
    Session session;

    if (!login_menu(&session)) {
        printf("Programa baigta.\n");
        return 0;
    }

    Car cars[MAX_CARS];
    int vehAmount = loadVehicles(cars, MAX_CARS);
    int choice;

    do {
        printf("\n-------------------------\n");
        printf("1. Auto registravimas\n");
        printf("2. Duomenu baze\n");
        printf("3. Filtravimo sistema\n");
        printf("4. Valdymas\n");
        if (strcmp(session.role, "ADMIN") == 0) printf("5. Admin panel\n");
        printf("0. Exit\n");
        printf("-------------------------\n");
        printf("Pasirinkti: ");
        scanf("%d", &choice);

        if (choice == 1) {
            getchar();
            registerVehicle(cars, &vehAmount);
        } else if (choice == 2) {
            int limit;
            printf("Kiek automobiliu parodyti? (0 - visi): ");
            scanf("%d", &limit);
            getVehicles(cars, vehAmount, limit);
        } else if (choice == 5 && strcmp(session.role, "ADMIN") == 0) {
            admin_panel();
        }
    } while (choice != 0);

    saveVehicles(cars, vehAmount);
    printf("Programa baigta.\n");

    return 0;
}
