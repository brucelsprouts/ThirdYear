#include "snackaroo_dish.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to safely read strings
void read_string(char *buffer, int max_len) {
    if (fgets(buffer, max_len, stdin) != NULL) {
        // Remove trailing newline character if present
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

// Create a new dish node
Dish *create_dish(int code, const char *name, const char *restaurant, float rating, float price) {
    Dish *newDish = (Dish *)malloc(sizeof(Dish));
    if (newDish == NULL) {
        fprintf(stderr, "Memory allocation failed for new dish.\n");
        return NULL;
    }
    newDish->code = code;
    strncpy(newDish->name, name, MAX_DISH_NAME_LEN - 1);
    newDish->name[MAX_DISH_NAME_LEN - 1] = '\0';
    strncpy(newDish->restaurant, restaurant, MAX_RESTAURANT_NAME_LEN - 1);
    newDish->restaurant[MAX_RESTAURANT_NAME_LEN - 1] = '\0';
    newDish->rating = rating;
    newDish->price = price;
    newDish->next = NULL;
    return newDish;
}

// Insert a new dish into the linked list (sorted by code for simplicity in searching/updating)
Dish *insert_dish(Dish *head, int code, const char *name, const char *restaurant, float rating, float price) {
    Dish *newDish = create_dish(code, name, restaurant, rating, price);
    if (newDish == NULL) {
        return head;
    }

    // Check for duplicate code
    if (search_dish(head, code) != NULL) {
        fprintf(stderr, "Error: Dish with code %d already exists.\n", code);
        free(newDish);
        return head;
    }

    if (head == NULL || head->code >= newDish->code) {
        newDish->next = head;
        return newDish;
    }

    Dish *current = head;
    while (current->next != NULL && current->next->code < newDish->code) {
        current = current->next;
    }
    newDish->next = current->next;
    current->next = newDish;
    return head;
}

// Search for a dish by code
Dish *search_dish(Dish *head, int code) {
    Dish *current = head;
    while (current != NULL) {
        if (current->code == code) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Update an existing dish
Dish *update_dish(Dish *head, int code, const char *name, const char *restaurant, float rating, float price) {
    Dish *dishToUpdate = search_dish(head, code);
    if (dishToUpdate != NULL) {
        strncpy(dishToUpdate->name, name, MAX_DISH_NAME_LEN - 1);
        dishToUpdate->name[MAX_DISH_NAME_LEN - 1] = '\0';
        strncpy(dishToUpdate->restaurant, restaurant, MAX_RESTAURANT_NAME_LEN - 1);
        dishToUpdate->restaurant[MAX_RESTAURANT_NAME_LEN - 1] = '\0';
        dishToUpdate->rating = rating;
        dishToUpdate->price = price;
        return head;
    }
    fprintf(stderr, "Error: Dish with code %d not found for update.\n", code);
    return head;
}

// Erase a dish by code
Dish *erase_dish(Dish *head, int code) {
    if (head == NULL) {
        fprintf(stderr, "Error: Dish list is empty.\n");
        return NULL;
    }

    Dish *current = head;
    Dish *prev = NULL;

    // If head node itself holds the code to be erased
    if (current != NULL && current->code == code) {
        head = current->next;
        free(current);
        printf("Dish with code %d erased successfully.\n", code);
        return head;
    }

    // Search for the code to be erased, keep track of the previous node
    while (current != NULL && current->code != code) {
        prev = current;
        current = current->next;
    }

    // If code was not present in linked list
    if (current == NULL) {
        fprintf(stderr, "Error: Dish with code %d not found for erasure.\n", code);
        return head;
    }

    // Unlink the node from the linked list
    prev->next = current->next;
    free(current);
    printf("Dish with code %d erased successfully.\n", code);
    return head;
}

// Print a single dish's details
void print_dish(const Dish *dish) {
    if (dish != NULL) {
        printf("Dish Code: %d\n", dish->code);
        printf("Dish Name: %s\n", dish->name);
        printf("Restaurant: %s\n", dish->restaurant);
        printf("Rating: %.1f\n", dish->rating);
        printf("Price: $%.2f\n", dish->price);
    } else {
        printf("Dish not found.\n");
    }
}

// Print all dishes in a table format
void print_all_dishes(const Dish *head) {
    if (head == NULL) {
        printf("No dishes in the database.\n");
        return;
    }
    printf("%-10s %-30s %-30s %-10s %-10s\n", "Code", "Name", "Restaurant", "Rating", "Price");
    printf("----------------------------------------------------------------------------------\n");
    const Dish *current = head;
    while (current != NULL) {
        printf("%-10d %-30s %-30s %-10.1f %-10.2f\n",
               current->code, current->name, current->restaurant, current->rating, current->price);
        current = current->next;
    }
}

// Clear all dishes from the list and free memory
void clear_all_dishes(Dish *head) {
    Dish *current = head;
    Dish *next_dish;
    while (current != NULL) {
        next_dish = current->next;
        free(current);
        current = next_dish;
    }
}