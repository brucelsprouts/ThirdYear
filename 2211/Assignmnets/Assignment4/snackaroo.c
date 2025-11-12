#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DISHES 100
#define MAX_NAME_LENGTH 100

// Structure to represent a single dish
typedef struct {
    int dishCode;
    char dishName[MAX_NAME_LENGTH];
    char restaurantName[MAX_NAME_LENGTH];
    float customerRating;
    float price;
    int isEmpty; // Flag to indicate if the slot is empty
} Dish;

// Global array to store dishes
Dish dishes[MAX_DISHES];
int numDishes = 0;

// Function prototypes
void displayMenu();
void insertDish();
void searchDish();
void updateDish();
void printDishes();
int findDishIndex(int code);
void clearInputBuffer();

// Clears the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Finds the index of a dish by its code, returns the index if found, -1 otherwise
int findDishIndex(int code) {
    for (int i = 0; i < MAX_DISHES; i++) {
        if (!dishes[i].isEmpty && dishes[i].dishCode == code) {
            return i;
        }
    }
    return -1;
}

// Inserts a new dish into the database
void insertDish() {
    if (numDishes == MAX_DISHES) {
        printf("Database is full. Cannot insert more dishes.\n");
        return;
    }

    int code;
    char nameBuffer[MAX_NAME_LENGTH * 2];
    float rating, price;
    int dishIndex = -1;

    while (1) {
        printf("\tEnter dish code: ");
        if (scanf("%d", &code) != 1) {
            printf("Invalid input. Please enter an integer for dish code.\n");
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        if (code < 0) {
            printf("Dish code must be positive. Please try again.\n");
            continue;
        }

        if (findDishIndex(code) != -1) {
            printf("Dish with code %d already exists. Please try again with a unique code.\n", code);
            continue;
        }
        break;
    }

    for (int i = 0; i < MAX_DISHES; i++) {
        if (dishes[i].isEmpty) {
            dishIndex = i;
            break;
        }
    }

    if (dishIndex == -1) {
        printf("Error: No empty slot found in database.\n");
        return;
    }

    dishes[dishIndex].dishCode = code;

    printf("\tEnter dish name: ");
    fgets(nameBuffer, sizeof(nameBuffer), stdin);
    nameBuffer[strcspn(nameBuffer, "\n")] = 0;
    strncpy(dishes[dishIndex].dishName, nameBuffer, MAX_NAME_LENGTH - 1);
    dishes[dishIndex].dishName[MAX_NAME_LENGTH - 1] = '\0';

    printf("\tEnter restaurant name: ");
    fgets(nameBuffer, sizeof(nameBuffer), stdin);
    nameBuffer[strcspn(nameBuffer, "\n")] = 0;
    strncpy(dishes[dishIndex].restaurantName, nameBuffer, MAX_NAME_LENGTH - 1);
    dishes[dishIndex].restaurantName[MAX_NAME_LENGTH - 1] = '\0';

    while (1) {
        printf("\tEnter dish rating (0.0-10.0): ");
        if (scanf("%f", &rating) != 1) {
            printf("Invalid input. Please enter a float value for dish rating.\n");
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        if (rating < 0.0 || rating > 10.0) {
            printf("Dish rating must be between 0.0 and 10.0. Please try again.\n");
            continue;
        }
        dishes[dishIndex].customerRating = rating;
        break;
    }

    while (1) {
        printf("\tEnter dish price (positive float): ");
        if (scanf("%f", &price) != 1) {
            printf("Invalid input. Please enter a float value for dish price.\n");
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        if (price <= 0.0) {
            printf("Dish price must be a positive float. Please try again.\n");
            continue;
        }
        dishes[dishIndex].price = price;
        break;
    }

    dishes[dishIndex].isEmpty = 0;
    numDishes++;
    printf("Dish inserted successfully.\n");
}

// Searches for a dish by code and prints its details
void searchDish() {
    int code;
    printf("\tEnter dish code: ");
    if (scanf("%d", &code) != 1) {
        printf("Invalid input. Please enter an integer for dish code.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = findDishIndex(code);
    if (index != -1) {
        printf("%-10s%-26s%-32s%-15s%-10s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
        printf("%-10d%-26s%-32s%-15.1f$%-9.2f\n",
               dishes[index].dishCode,
               dishes[index].dishName,
               dishes[index].restaurantName,
               dishes[index].customerRating,
               dishes[index].price);
    } else {
        printf("Dish with code %d not found.\n", code);
    }
}

// Updates an existing dish in the database
void updateDish() {
    int code;
    char nameBuffer[MAX_NAME_LENGTH * 2];
    float rating, price;

    printf("\tEnter dish code to update: ");
    if (scanf("%d", &code) != 1) {
        printf("Invalid input. Please enter an integer for dish code.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = findDishIndex(code);
    if (index != -1) {
        printf("Dish found. Enter new details:\n");

        printf("\tEnter dish name: ");
        fgets(nameBuffer, sizeof(nameBuffer), stdin);
        nameBuffer[strcspn(nameBuffer, "\n")] = 0;
        strncpy(dishes[index].dishName, nameBuffer, MAX_NAME_LENGTH - 1);
        dishes[index].dishName[MAX_NAME_LENGTH - 1] = '\0';

        printf("\tEnter restaurant name: ");
        fgets(nameBuffer, sizeof(nameBuffer), stdin);
        nameBuffer[strcspn(nameBuffer, "\n")] = 0;
        strncpy(dishes[index].restaurantName, nameBuffer, MAX_NAME_LENGTH - 1);
        dishes[index].restaurantName[MAX_NAME_LENGTH - 1] = '\0';

        while (1) {
            printf("\tEnter dish rating (0.0-10.0): ");
            if (scanf("%f", &rating) != 1) {
                printf("Invalid input. Please enter a float value for dish rating.\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            if (rating < 0.0 || rating > 10.0) {
                printf("Dish rating must be between 0.0 and 10.0. Please try again.\n");
                continue;
            }
            dishes[index].customerRating = rating;
            break;
        }

        while (1) {
            printf("\tEnter dish price (positive float): ");
            if (scanf("%f", &price) != 1) {
                printf("Invalid input. Please enter a float value for dish price.\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            if (price <= 0.0) {
                printf("Dish price must be a positive float. Please try again.\n");
                continue;
            }
            dishes[index].price = price;
            break;
        }
        printf("Dish updated successfully.\n");
    } else {
        printf("Dish with code %d not found.\n", code);
    }
}

// Prints all dishes in the database
void printDishes() {
    if (numDishes == 0) {
        printf("No dishes in the database.\n");
        return;
    }

    printf("%-10s%-26s%-32s%-15s%-10s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
    for (int i = 0; i < MAX_DISHES; i++) {
        if (!dishes[i].isEmpty) {
            printf("%-10d%-26s%-32s%-15.1f$%-9.2f\n",
                   dishes[i].dishCode,
                   dishes[i].dishName,
                   dishes[i].restaurantName,
                   dishes[i].customerRating,
                   dishes[i].price);
        }
    }
}

// Displays the main menu
void displayCode() {
    printf("Enter operation code: ");
}

// Main function
int main() {
    for (int i = 0; i < MAX_DISHES; i++) {
        dishes[i].isEmpty = 1;
    }
    printf("**********************\n");
    printf("* 2211 Snackaroo App *\n");
    printf("**********************\n\n");
    
    char command;
    while (1) {
        displayCode();
        if (scanf(" %c", &command) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a single character command.\n");
            continue;
        }
        clearInputBuffer();

        switch (tolower(command)) {
            case 'i':
                insertDish();
                break;
            case 's':
                searchDish();
                break;
            case 'u':
                updateDish();
                break;
            case 'p':
                printDishes();
                break;
            case 'q':
                printf("Quitting Snackaroo App. Goodbye!\n");
                return 0;
            default:
                printf("Invalid command. Please use i, s, u, p, or q.\n");
                break;
        }
        printf("\n");
    }
    return 0;
}