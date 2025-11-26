#ifndef SNACKAROO_DISH_H
#define SNACKAROO_DISH_H

#include "snackaroo.h"

// Structure to represent a dish
typedef struct Dish {
    int code;
    char name[MAX_DISH_NAME_LEN];
    char restaurant[MAX_RESTAURANT_NAME_LEN];
    float rating;
    float price;
    struct Dish *next;
} Dish;

// Function prototypes for dish management
Dish *create_dish(int code, const char *name, const char *restaurant, float rating, float price);
Dish *insert_dish(Dish *head, int code, const char *name, const char *restaurant, float rating, float price);
Dish *search_dish(Dish *head, int code);
Dish *update_dish(Dish *head, int code, const char *name, const char *restaurant, float rating, float price);
Dish *erase_dish(Dish *head, int code);
void print_dish(const Dish *dish);
void print_all_dishes(const Dish *head);
void clear_all_dishes(Dish *head);

#endif // SNACKAROO_DISH_H