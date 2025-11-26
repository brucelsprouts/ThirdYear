#ifndef SNACKAROO_DRIVER_H
#define SNACKAROO_DRIVER_H

#include "snackaroo.h"

// Structure to represent a delivery driver
typedef struct Driver {
    int code;
    char name[MAX_DRIVER_NAME_LEN];
    VehicleColor vehicle_color;
    char license_plate[MAX_LICENSE_PLATE_LEN];
    struct Driver *next;
} Driver;

// Function prototypes for driver management
int is_valid_license_plate(const char *plate);
const char* get_vehicle_color_string(VehicleColor color);
Driver *create_driver(int code, const char *name, VehicleColor color, const char *license_plate);
Driver *insert_driver(Driver *head, int code, const char *name, VehicleColor color, const char *license_plate);
Driver *search_driver(Driver *head, int code);
Driver *update_driver(Driver *head, int code, const char *name, VehicleColor color, const char *license_plate);
Driver *erase_driver(Driver *head, int code);
void print_driver(const Driver *driver);
void print_all_drivers(const Driver *head);
void clear_all_drivers(Driver *head);

#endif // SNACKAROO_DRIVER_H