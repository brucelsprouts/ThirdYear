#include <stdio.h>
#include <stdlib.h> // For malloc and free, though not strictly needed for fixed-size array
#include <string.h> // For strtok, if parsing input string
#include <ctype.h>  // For isdigit, if validating input characters

// Function prototypes
void print_array(const int arr[], int size);
void print_reverse_array(const int arr[], int size);
void print_even_elements(const int arr[], int size);
void sum_array_elements(const int arr[], int size);
void print_sorted_array(const int arr[], int size);
void print_swapped_first_last(const int arr[], int size);

int main() {
    int num_integers;

    // Ask the user for how many integers they will provide.
    // Assume the user will not lie and will provide between 5 and 12 integers.
    do {
        printf("Please enter the number of integers to process (5-12): ");
        scanf("%d", &num_integers);
    } while (num_integers < 5 || num_integers > 12);

    // Declare a VLA (Variable Length Array) based on user input
    int arr[num_integers];
    
    // Print the number the user gave and the size of the array in bytes
    printf("There is enough room in your array for %d integers (%zu bytes)\n", num_integers, sizeof(arr));

    // Prompt the user for the list of integers
    printf("Please enter your integers separated by spaces: ");
    for (int i = 0; i < num_integers; i++) {
        scanf("%d", &arr[i]);
    }

    // Part 1: Print out the elements of the array and their positions
    printf("\nPart 1:\n");
    print_array(arr, num_integers);

    // Part 2: Print out the elements of the array in reverse order and their positions
    printf("\nPart 2:\n");
    print_reverse_array(arr, num_integers);

    // Part 3: Print out all the even elements in the array and their positions
    printf("\nPart 3:\n");
    print_even_elements(arr, num_integers);

    // Part 4: Print out the sum of all values in the array
    printf("\nPart 4:\n");
    sum_array_elements(arr, num_integers);

    // Part 5: Print out the elements of the array from smallest to largest (ascending order) and their positions
    printf("\nPart 5:\n");
    print_sorted_array(arr, num_integers);

    // Part 6: Print out the elements of the array except the first and last element are swapped and the position they are in
    printf("\nPart 6:\n");
    print_swapped_first_last(arr, num_integers);

    return 0;
}

// Part 1: Prints the elements of the array and their positions
void print_array(const int arr[], int size) {
    printf("     Your array is: ");
    for (int i = 0; i < size; i++) {
        printf("[%d] = %d", i, arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Part 2: Prints the elements of the array in reverse order and their positions
void print_reverse_array(const int arr[], int size) {
    printf("     Your array in reverse is: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("[%d] = %d", i, arr[i]);
        if (i > 0) {
            printf(", ");
        }
    }
    printf("\n");
}

// Part 3: Prints all the even elements in the array and their positions
void print_even_elements(const int arr[], int size) {
    printf("     The even elements in the array is: ");
    int first_even = 1; // Flag to handle comma placement
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            if (!first_even) {
                printf(", ");
            }
            printf("[%d] = %d", i, arr[i]);
            first_even = 0;
        }
    }
    if (first_even) { // If no even numbers were found
        printf("None");
    }
    printf("\n");
}

// Part 4: Prints the sum of all values in the array
void sum_array_elements(const int arr[], int size) {
    long long sum = 0; // Use long long to prevent overflow for large sums
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    printf("     The sum of all values in your array is: %lld\n", sum);
}

// Part 5: Prints the elements of the array from smallest to largest (ascending order) and their positions
void print_sorted_array(const int arr[], int size) {
    // Create a temporary array of structs to store value and original index
    struct Element {
        int value;
        int original_index;
    };

    struct Element temp_arr[size];
    for (int i = 0; i < size; i++) {
        temp_arr[i].value = arr[i];
        temp_arr[i].original_index = i;
    }

    // Sort the temporary array based on values
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (temp_arr[i].value > temp_arr[j].value) {
                struct Element temp = temp_arr[i];
                temp_arr[i] = temp_arr[j];
                temp_arr[j] = temp;
            }
        }
    }

    printf("     Your array in sorted order is: ");
    for (int i = 0; i < size; i++) {
        printf("[%d] = %d", temp_arr[i].original_index, temp_arr[i].value);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Part 6: Prints the elements of the array with the first and last elements swapped
void print_swapped_first_last(const int arr[], int size) {
    printf("     Your array with first and last element switched is: ");
    if (size < 2) { // Handle cases where there are less than 2 elements
        print_array(arr, size); // Just print the original if not enough elements to swap
        return;
    }

    // Create a temporary array to hold the modified order
    int temp_arr[size];
    for (int i = 0; i < size; i++) {
        temp_arr[i] = arr[i];
    }

    // Swap the first and last elements in the temporary array
    int temp = temp_arr[0];
    temp_arr[0] = temp_arr[size - 1];
    temp_arr[size - 1] = temp;

    for (int i = 0; i < size; i++) {
        printf("[%d] = %d", i, temp_arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}