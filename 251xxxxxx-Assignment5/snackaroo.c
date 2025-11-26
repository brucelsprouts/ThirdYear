#include "snackaroo.h"
#include "snackaroo_dish.h"
#include "snackaroo_driver.h"

// Global head pointers for the linked lists
Dish *dish_head = NULL;
Driver *driver_head = NULL;

void print_detailed_help() {
    printf("************************************\n");
    printf("* Welcome to the 2211 Snackaroo App *\n");
    printf("************************************\n\n");
    printf("This program allows you to manage dishes and drivers for a snack delivery service.\n");
    printf("You can perform various operations like inserting, searching, updating, and erasing dishes and drivers.\n\n");
    printf("--- Main Menu Commands ---\n");
    printf("  h: Display this comprehensive help message\n");
    printf("  q: Quit the program (Warning: all unsaved data will be lost)\n");
    printf("  m: Access the 'Dish Control Menu' for dish management\n");
    printf("  a: Access the 'Driver Control Menu' for driver management\n");
    printf("------------------------------------\n\n");
}

void print_main_menu() {
    printf("--- Main Menu ---\n");
    printf("  h: Help\n");
    printf("  q: Quit\n");
    printf("  m: Dishes\n");
    printf("  a: Drivers\n");
    printf("-----------------\n\n");
}

// Function to get a command from the user
char get_command() {
    char command;
    printf("\tEnter command: ");
    scanf(" %c", &command);
    while (getchar() != '\n');
    return command;
}

void control_dishes() {
    char command;
    int code;
    char name[MAX_DISH_NAME_LEN];
    char restaurant[MAX_RESTAURANT_NAME_LEN];
    float rating, price;
    Dish *found_dish;

    printf("\n--- Dish Control Menu ---\n");
    printf("  i: Insert a new dish\n");
    printf("  s: Search for a dish by code\n");
    printf("  u: Update an existing dish by code\n");
    printf("  e: Erase a dish by code\n");
    printf("  p: Print all dishes currently in the system\n");
    printf("  b: Return to the main menu\n");
    printf("-------------------------\n\n");

    while (1) {
        printf("\tEnter dish command: ");
        scanf(" %c", &command);
        while (getchar() != '\n');

        switch (command) {
            case 'i':
                printf("\tEnter dish code: ");
                scanf("%d", &code);
                while (getchar() != '\n');

                if (code < 0) {
                    printf("Error: Dish code must be positive.\n");
                    break;
                }
                if (search_dish(dish_head, code) != NULL) {
                    printf("Error: Dish with code %d already exists.\n", code);
                    break;
                }

                printf("\tEnter dish name (up to %d characters): ", MAX_DISH_NAME_LEN - 1);
                read_string(name, MAX_DISH_NAME_LEN);

                printf("\tEnter restaurant name (up to %d characters): ", MAX_RESTAURANT_NAME_LEN - 1);
                read_string(restaurant, MAX_RESTAURANT_NAME_LEN);

                printf("\tEnter dish rating (0.0-10.0, one decimal): ");
                scanf("%f", &rating);
                while (getchar() != '\n');
                if (rating < 0.0 || rating > 10.0) {
                    printf("Error: Rating must be between 0.0 and 10.0.\n");
                    break;
                }

                printf("\tEnter dish price (positive float, two decimals): ");
                scanf("%f", &price);
                while (getchar() != '\n');
                if (price <= 0.0) {
                    printf("Error: Price must be a positive float.\n");
                    break;
                }

                dish_head = insert_dish(dish_head, code, name, restaurant, rating, price);
                printf("Dish inserted successfully.\n");
                break;

            case 's':
                printf("\tEnter dish code to search: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_dish = search_dish(dish_head, code);
                print_dish(found_dish);
                break;

            case 'u':
                printf("\tEnter dish code to update: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_dish = search_dish(dish_head, code);
                if (found_dish == NULL) {
                    printf("Error: Dish with code %d not found for update.\n", code);
                    break;
                }

                printf("\tEnter new dish name (up to %d characters): ", MAX_DISH_NAME_LEN - 1);
                read_string(name, MAX_DISH_NAME_LEN);

                printf("\tEnter new restaurant name (up to %d characters): ", MAX_RESTAURANT_NAME_LEN - 1);
                read_string(restaurant, MAX_RESTAURANT_NAME_LEN);

                printf("\tEnter new dish rating (0.0-10.0, one decimal): ");
                scanf("%f", &rating);
                while (getchar() != '\n');
                if (rating < 0.0 || rating > 10.0) {
                    printf("Error: Rating must be between 0.0 and 10.0.\n");
                    break;
                }

                printf("\tEnter new dish price (positive float, two decimals): ");
                scanf("%f", &price);
                while (getchar() != '\n');
                if (price <= 0.0) {
                    printf("Error: Price must be a positive float.\n");
                    break;
                }

                dish_head = update_dish(dish_head, code, name, restaurant, rating, price);
                printf("Dish updated successfully.\n");
                break;

            case 'e':
                printf("\tEnter dish code to erase: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                dish_head = erase_dish(dish_head, code);
                break;

            case 'p':
                print_all_dishes(dish_head);
                break;

            case 'b':
                return;

            default:
                printf("Invalid command for dish control. Please try again.\n");
                break;
        }
    }
}

void control_drivers() {
    char command;
    int code, color_int;
    char name[MAX_DRIVER_NAME_LEN];
    char license_plate[MAX_LICENSE_PLATE_LEN];
    Driver *found_driver;
    VehicleColor vehicle_color;

    printf("\n--- Driver Control Menu ---\n");
    printf("  i: Insert a new driver\n");
    printf("  s: Search for a driver by code\n");
    printf("  u: Update an existing driver by code\n");
    printf("  e: Erase a driver by code\n");
    printf("  p: Print all drivers currently in the system\n");
    printf("  b: Return to the main menu\n");
    printf("---------------------------\n\n");

    while (1) {
        printf("\tEnter driver command: ");
        scanf(" %c", &command);
        while (getchar() != '\n');

        switch (command) {
            case 'i':
                printf("\tEnter driver code: ");
                scanf("%d", &code);
                while (getchar() != '\n');

                if (code < 0) {
                    printf("Error: Driver code must be positive.\n");
                    break;
                }
                if (search_driver(driver_head, code) != NULL) {
                    printf("Error: Driver with code %d already exists.\n", code);
                    break;
                }

                printf("\tEnter driver name (up to %d characters): ", MAX_DRIVER_NAME_LEN - 1);
                read_string(name, MAX_DRIVER_NAME_LEN);

                printf("\tEnter vehicle color (0=red, 1=green, 2=blue, 3=grey, 4=white, 5=black, 6=other): ");
                scanf("%d", &color_int);
                while (getchar() != '\n');
                if (color_int < 0 || color_int > 6) {
                    printf("Error: Invalid color code.\n");
                    break;
                }
                vehicle_color = (VehicleColor)color_int;

                printf("\tEnter license plate (2-8 alphanumeric characters or spaces): ");
                read_string(license_plate, MAX_LICENSE_PLATE_LEN);
                if (!is_valid_license_plate(license_plate)) {
                    printf("Error: Invalid license plate format.\n");
                    break;
                }

                driver_head = insert_driver(driver_head, code, name, vehicle_color, license_plate);
                printf("Driver inserted successfully.\n");
                break;

            case 's':
                printf("\tEnter driver code to search: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_driver = search_driver(driver_head, code);
                print_driver(found_driver);
                break;

            case 'u':
                printf("\tEnter driver code to update: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_driver = search_driver(driver_head, code);
                if (found_driver == NULL) {
                    printf("Error: Driver with code %d not found for update.\n", code);
                    break;
                }

                printf("\tEnter new driver name (up to %d characters): ", MAX_DRIVER_NAME_LEN - 1);
                read_string(name, MAX_DRIVER_NAME_LEN);

                printf("\tEnter new vehicle color (0=red, 1=green, 2=blue, 3=grey, 4=white, 5=black, 6=other): ");
                scanf("%d", &color_int);
                while (getchar() != '\n');
                if (color_int < 0 || color_int > 6) {
                    printf("Error: Invalid color code.\n");
                    break;
                }
                vehicle_color = (VehicleColor)color_int;

                printf("\tEnter new license plate (2-8 alphanumeric characters or spaces): ");
                read_string(license_plate, MAX_LICENSE_PLATE_LEN);
                if (!is_valid_license_plate(license_plate)) {
                    printf("Error: Invalid license plate format.\n");
                    break;
                }

                driver_head = update_driver(driver_head, code, name, vehicle_color, license_plate);
                printf("Driver updated successfully.\n");
                break;

            case 'e':
                printf("\tEnter driver code to erase: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                driver_head = erase_driver(driver_head, code);
                break;

            case 'p': // Print all drivers
                print_all_drivers(driver_head);
                break;

            case 'b': // Back to main menu
                return;

            default:
                printf("Invalid command for driver control. Please try again.\n");
                break;
        }
    }
}

int main() {
    char command;

    printf("**********************\n");
    printf("* 2211 Snackaroo App *\n");
    printf("**********************\n\n");

    do {
        print_main_menu();
        command = get_command();

        switch (command) {
            case 'h':
                print_detailed_help();
                break;
            case 'q':
                printf("Quitting Snackaroo. All data will be lost.\n\n");
                break;
            case 'm':
                control_dishes();
                break;
            case 'a':
                control_drivers();
                break;
            default:
                printf("Invalid command. Please enter 'h' for help.\n\n");
                break;
        }
    } while (command != 'q');

    // Free all allocated memory before exiting
    clear_all_dishes(dish_head);
    clear_all_drivers(driver_head);

    return 0;
}