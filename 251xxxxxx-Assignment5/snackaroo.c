#include "snackaroo.h"
#include "snackaroo_dish.h"
#include "snackaroo_driver.h"

// Global head pointers for the linked lists
Dish *dish_head = NULL;
Driver *driver_head = NULL;

// Function to print help messages
void print_help() {
    printf("\n--- Snackaroo Menu ---\n");
    printf("h: Print help\n");
    printf("q: Quit the program\n");
    printf("m: Control dishes\n");
    printf("a: Control drivers\n");
    printf("----------------------\n");
}

// Function to get a command from the user
char get_command() {
    char command;
    printf("Enter command (h for help): ");
    scanf(" %c", &command); // Space before %c to consume any leftover newline character
    while (getchar() != '\n'); // Clear input buffer
    return command;
}

// Function to control dishes
void control_dishes() {
    char command;
    int code;
    char name[MAX_DISH_NAME_LEN];
    char restaurant[MAX_RESTAURANT_NAME_LEN];
    float rating, price;
    Dish *found_dish;

    printf("\n--- Dish Control Menu ---\n");
    printf("i: Insert a new dish\n");
    printf("s: Search for a dish\n");
    printf("u: Update a dish\n");
    printf("e: Erase a dish\n");
    printf("p: Print all dishes\n");
    printf("b: Back to main menu\n");
    printf("-------------------------\n");

    while (1) {
        printf("Enter dish command: ");
        scanf(" %c", &command);
        while (getchar() != '\n');

        switch (command) {
            case 'i': // Insert a new dish
                printf("Enter dish code: ");
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

                printf("Enter dish name (up to %d characters): ", MAX_DISH_NAME_LEN - 1);
                read_string(name, MAX_DISH_NAME_LEN);

                printf("Enter restaurant name (up to %d characters): ", MAX_RESTAURANT_NAME_LEN - 1);
                read_string(restaurant, MAX_RESTAURANT_NAME_LEN);

                printf("Enter dish rating (0.0-10.0, one decimal): ");
                scanf("%f", &rating);
                while (getchar() != '\n');
                if (rating < 0.0 || rating > 10.0) {
                    printf("Error: Rating must be between 0.0 and 10.0.\n");
                    break;
                }

                printf("Enter dish price (positive float, two decimals): ");
                scanf("%f", &price);
                while (getchar() != '\n');
                if (price <= 0.0) {
                    printf("Error: Price must be a positive float.\n");
                    break;
                }

                dish_head = insert_dish(dish_head, code, name, restaurant, rating, price);
                printf("Dish inserted successfully.\n");
                break;

            case 's': // Search for a dish
                printf("Enter dish code to search: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_dish = search_dish(dish_head, code);
                print_dish(found_dish);
                break;

            case 'u': // Update a dish
                printf("Enter dish code to update: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_dish = search_dish(dish_head, code);
                if (found_dish == NULL) {
                    printf("Error: Dish with code %d not found for update.\n", code);
                    break;
                }

                printf("Enter new dish name (up to %d characters): ", MAX_DISH_NAME_LEN - 1);
                read_string(name, MAX_DISH_NAME_LEN);

                printf("Enter new restaurant name (up to %d characters): ", MAX_RESTAURANT_NAME_LEN - 1);
                read_string(restaurant, MAX_RESTAURANT_NAME_LEN);

                printf("Enter new dish rating (0.0-10.0, one decimal): ");
                scanf("%f", &rating);
                while (getchar() != '\n');
                if (rating < 0.0 || rating > 10.0) {
                    printf("Error: Rating must be between 0.0 and 10.0.\n");
                    break;
                }

                printf("Enter new dish price (positive float, two decimals): ");
                scanf("%f", &price);
                while (getchar() != '\n');
                if (price <= 0.0) {
                    printf("Error: Price must be a positive float.\n");
                    break;
                }

                dish_head = update_dish(dish_head, code, name, restaurant, rating, price);
                printf("Dish updated successfully.\n");
                break;

            case 'e': // Erase a dish
                printf("Enter dish code to erase: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                dish_head = erase_dish(dish_head, code);
                break;

            case 'p': // Print all dishes
                print_all_dishes(dish_head);
                break;

            case 'b': // Back to main menu
                return;

            default:
                printf("Invalid command for dish control. Please try again.\n");
                break;
        }
    }
}

// Function to control drivers
void control_drivers() {
    char command;
    int code, color_int;
    char name[MAX_DRIVER_NAME_LEN];
    char license_plate[MAX_LICENSE_PLATE_LEN];
    Driver *found_driver;
    VehicleColor vehicle_color;

    printf("\n--- Driver Control Menu ---\n");
    printf("i: Insert a new driver\n");
    printf("s: Search for a driver\n");
    printf("u: Update a driver\n");
    printf("e: Erase a driver\n");
    printf("p: Print all drivers\n");
    printf("b: Back to main menu\n");
    printf("---------------------------\n");

    while (1) {
        printf("Enter driver command: ");
        scanf(" %c", &command);
        while (getchar() != '\n');

        switch (command) {
            case 'i': // Insert a new driver
                printf("Enter driver code: ");
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

                printf("Enter driver name (up to %d characters): ", MAX_DRIVER_NAME_LEN - 1);
                read_string_driver(name, MAX_DRIVER_NAME_LEN);

                printf("Enter vehicle color (0=red, 1=green, 2=blue, 3=grey, 4=white, 5=black, 6=other): ");
                scanf("%d", &color_int);
                while (getchar() != '\n');
                if (color_int < 0 || color_int > 6) {
                    printf("Error: Invalid color code.\n");
                    break;
                }
                vehicle_color = (VehicleColor)color_int;

                printf("Enter license plate (2-8 alphanumeric characters or spaces): ");
                read_string_driver(license_plate, MAX_LICENSE_PLATE_LEN);
                if (!is_valid_license_plate(license_plate)) {
                    printf("Error: Invalid license plate format.\n");
                    break;
                }

                driver_head = insert_driver(driver_head, code, name, vehicle_color, license_plate);
                printf("Driver inserted successfully.\n");
                break;

            case 's': // Search for a driver
                printf("Enter driver code to search: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_driver = search_driver(driver_head, code);
                print_driver(found_driver);
                break;

            case 'u': // Update a driver
                printf("Enter driver code to update: ");
                scanf("%d", &code);
                while (getchar() != '\n');
                found_driver = search_driver(driver_head, code);
                if (found_driver == NULL) {
                    printf("Error: Driver with code %d not found for update.\n", code);
                    break;
                }

                printf("Enter new driver name (up to %d characters): ", MAX_DRIVER_NAME_LEN - 1);
                read_string_driver(name, MAX_DRIVER_NAME_LEN);

                printf("Enter new vehicle color (0=red, 1=green, 2=blue, 3=grey, 4=white, 5=black, 6=other): ");
                scanf("%d", &color_int);
                while (getchar() != '\n');
                if (color_int < 0 || color_int > 6) {
                    printf("Error: Invalid color code.\n");
                    break;
                }
                vehicle_color = (VehicleColor)color_int;

                printf("Enter new license plate (2-8 alphanumeric characters or spaces): ");
                read_string_driver(license_plate, MAX_LICENSE_PLATE_LEN);
                if (!is_valid_license_plate(license_plate)) {
                    printf("Error: Invalid license plate format.\n");
                    break;
                }

                driver_head = update_driver(driver_head, code, name, vehicle_color, license_plate);
                printf("Driver updated successfully.\n");
                break;

            case 'e': // Erase a driver
                printf("Enter driver code to erase: ");
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

    do {
        print_help();
        command = get_command();

        switch (command) {
            case 'h':
                // Help is already printed by print_help()
                break;
            case 'q':
                printf("Quitting Snackaroo. All data will be lost.\n");
                break;
            case 'm':
                control_dishes();
                break;
            case 'a':
                control_drivers();
                break;
            default:
                printf("Invalid command. Please try again.\n");
                break;
        }
    } while (command != 'q');

    // Free all allocated memory before exiting
    clear_all_dishes(dish_head);
    clear_all_drivers(driver_head);

    return 0;
}