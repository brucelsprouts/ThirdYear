#ifndef SNACKAROO_H
#define SNACKAROO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Common macros for string lengths
#define MAX_DISH_NAME_LEN 100
#define MAX_RESTAURANT_NAME_LEN 100
#define MAX_DRIVER_NAME_LEN 50
#define MAX_LICENSE_PLATE_LEN 9 // 2-8 alphanumeric + 1 for null terminator

// Driver vehicle colors
typedef enum {
    RED,
    GREEN,
    BLUE,
    GREY,
    WHITE,
    BLACK,
    OTHER
} VehicleColor;

// Function prototypes for main menu
void print_help();
char get_command();
void control_dishes();
void control_drivers();

#endif // SNACKAROO_H