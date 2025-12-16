#include <stdio.h>
#include <string.h>
#include "login.h"
#include "admin.h"
#include "car.h"
#include "util.h"

int main() {
    Session session;
    ensure_data_dir();
    if (!login_menu(&session)) {
        printf("Programa baigta.\n");
        return 0;
    }

    Car cars[MAX_CARS];
    int car_count = load_cars(cars, MAX_CARS);
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

        if (choice == 1) {
            Car new_car;
            printf("\nValstybiniai numeriai: ");
            scanf("%31s", new_car.number);
            printf("Marke: ");
            scanf("%31s", new_car.make);
            printf("Spalva: ");
            scanf("%31s", new_car.color);
            printf("Kuro tipas: ");
            scanf("%31s", new_car.fuel);
            printf("Kategorija: ");
            scanf("%31s", new_car.category);
            if (add_car(cars, &car_count, new_car)) {
                save_cars(cars, car_count);
                printf("Automobilis uzregistruotas!\n");
            } else {
                printf("Nepavyko uzregistruoti (duomenu bazes limitas)!\n");
            }
        } else if (choice == 2) {
            int limit;
            printf("Kiek automobiliu parodyti? (0 - visi): ");
            scanf("%d", &limit);
            print_cars(cars, car_count, limit);
        } else if (choice == 5 && strcmp(session.role, "ADMIN") == 0) {
            admin_panel();
        }
    } while (choice != 0);
    save_cars(cars, car_count);
    printf("Programa baigta.\n");
    return 0;
}
