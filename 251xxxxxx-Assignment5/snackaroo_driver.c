#include "snackaroo_driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isalnum

// Helper function to safely read strings (can be moved to snackaroo.c or a common_utils.c if preferred)
void read_string_driver(char *buffer, int max_len) {
    if (fgets(buffer, max_len, stdin) != NULL) {
        // Remove trailing newline character if present
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

// Helper function to convert VehicleColor enum to string
const char* get_vehicle_color_string(VehicleColor color) {
    switch (color) {
        case RED: return "red";
        case GREEN: return "green";
        case BLUE: return "blue";
        case GREY: return "grey";
        case WHITE: return "white";
        case BLACK: return "black";
        case OTHER: return "other";
        default: return "unknown";
    }
}

// Helper function to validate license plate characters
int is_valid_license_plate(const char *plate) {
    if (strlen(plate) < 2 || strlen(plate) > 8) {
        return 0; // Length constraint
    }
    for (int i = 0; plate[i] != '\0'; i++) {
        if (!isalnum((unsigned char)plate[i]) && plate[i] != ' ') {
            return 0; // Contains non-alphanumeric and non-space character
        }
    }
    return 1;
}

// Create a new driver node
Driver *create_driver(int code, const char *name, VehicleColor color, const char *license_plate) {
    Driver *newDriver = (Driver *)malloc(sizeof(Driver));
    if (newDriver == NULL) {
        fprintf(stderr, "Memory allocation failed for new driver.\n");
        return NULL;
    }
    newDriver->code = code;
    strncpy(newDriver->name, name, MAX_DRIVER_NAME_LEN - 1);
    newDriver->name[MAX_DRIVER_NAME_LEN - 1] = '\0';
    newDriver->vehicle_color = color;
    strncpy(newDriver->license_plate, license_plate, MAX_LICENSE_PLATE_LEN - 1);
    newDriver->license_plate[MAX_LICENSE_PLATE_LEN - 1] = '\0';
    newDriver->next = NULL;
    return newDriver;
}

// Insert a new driver into the linked list (sorted by code)
Driver *insert_driver(Driver *head, int code, const char *name, VehicleColor color, const char *license_plate) {
    Driver *newDriver = create_driver(code, name, color, license_plate);
    if (newDriver == NULL) {
        return head;
    }

    // Check for duplicate code
    if (search_driver(head, code) != NULL) {
        fprintf(stderr, "Error: Driver with code %d already exists.\n", code);
        free(newDriver);
        return head;
    }

    if (head == NULL || head->code >= newDriver->code) {
        newDriver->next = head;
        return newDriver;
    }

    Driver *current = head;
    while (current->next != NULL && current->next->code < newDriver->code) {
        current = current->next;
    }
    newDriver->next = current->next;
    current->next = newDriver;
    return head;
}

// Search for a driver by code
Driver *search_driver(Driver *head, int code) {
    Driver *current = head;
    while (current != NULL) {
        if (current->code == code) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Update an existing driver
Driver *update_driver(Driver *head, int code, const char *name, VehicleColor color, const char *license_plate) {
    Driver *driverToUpdate = search_driver(head, code);
    if (driverToUpdate != NULL) {
        strncpy(driverToUpdate->name, name, MAX_DRIVER_NAME_LEN - 1);
        driverToUpdate->name[MAX_DRIVER_NAME_LEN - 1] = '\0';
        driverToUpdate->vehicle_color = color;
        strncpy(driverToUpdate->license_plate, license_plate, MAX_LICENSE_PLATE_LEN - 1);
        driverToUpdate->license_plate[MAX_LICENSE_PLATE_LEN - 1] = '\0';
        return head;
    }
    fprintf(stderr, "Error: Driver with code %d not found for update.\n", code);
    return head;
}

// Erase a driver by code
Driver *erase_driver(Driver *head, int code) {
    if (head == NULL) {
        fprintf(stderr, "Error: Driver list is empty.\n");
        return NULL;
    }

    Driver *current = head;
    Driver *prev = NULL;

    // If head node itself holds the code to be erased
    if (current != NULL && current->code == code) {
        head = current->next;
        free(current);
        printf("Driver with code %d erased successfully.\n", code);
        return head;
    }

    // Search for the code to be erased, keep track of the previous node
    while (current != NULL && current->code != code) {
        prev = current;
        current = current->next;
    }

    // If code was not present in linked list
    if (current == NULL) {
        fprintf(stderr, "Error: Driver with code %d not found for erasure.\n", code);
        return head;
    }

    // Unlink the node from the linked list
    prev->next = current->next;
    free(current);
    printf("Driver with code %d erased successfully.\n", code);
    return head;
}

// Print a single driver's details
void print_driver(const Driver *driver) {
    if (driver != NULL) {
        printf("Driver Code: %d\n", driver->code);
        printf("Driver Name: %s\n", driver->name);
        printf("Vehicle Color: %s\n", get_vehicle_color_string(driver->vehicle_color));
        printf("License Plate: %s\n", driver->license_plate);
    } else {
        printf("Driver not found.\n");
    }
}

// Print all drivers in a table format
void print_all_drivers(const Driver *head) {
    if (head == NULL) {
        printf("No drivers in the database.\n");
        return;
    }
    printf("%-10s %-30s %-15s %-15s\n", "Code", "Name", "Vehicle Color", "License Plate");
    printf("-----------------------------------------------------------------------\n");
    const Driver *current = head;
    while (current != NULL) {
        printf("%-10d %-30s %-15s %-15s\n",
               current->code, current->name, get_vehicle_color_string(current->vehicle_color), current->license_plate);
        current = current->next;
    }
}

// Clear all drivers from the list and free memory
void clear_all_drivers(Driver *head) {
    Driver *current = head;
    Driver *next_driver;
    while (current != NULL) {
        next_driver = current->next;
        free(current);
        current = next_driver;
    }
}