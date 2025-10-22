#include <stdio.h>

// Function prototypes
void print_array(const int arr[], int size);
void print_reverse_array(const int arr[], int size);
void print_even_elements(const int arr[], int size);
void sum_array_elements(const int arr[], int size);
void print_sorted_array(const int arr[], int size);
void print_swapped_first_last(const int arr[], int size);

int main() {
    int num_integers;

    // Ask the user for how many integers they will provide (between 5 and 12).
    do {
        printf("Please enter the number of integers to process: ");
        scanf("%d", &num_integers);
    } while (num_integers < 5 || num_integers > 12);
    int arr[num_integers];

    // Print the number the user gave you and size of the array in bytes (using sizeof)
    printf("There is enough room in your array for %d integers (%zu bytes)\n", num_integers, sizeof(arr));

    // Prompt the user for the list of integers.
    printf("Please enter your integers separated by spaces: ");
    for (int i = 0; i < num_integers; i++) {
        scanf("%d", &arr[i]);
    }

    // Part 1: Print out the elements of the array and which position they are in
    printf("Part 1:\n");
    print_array(arr, num_integers);

    // Part 2: Print out the elements of the array in reverse order and which position they are in
    printf("\nPart 2:\n");
    print_reverse_array(arr, num_integers);

    // Part 3: Print out all the even elements in the array and which position they are in
    printf("\nPart 3:\n");
    print_even_elements(arr, num_integers);

    // Part 4: Print out the sum of all values in the array
    printf("\nPart 4:\n");
    sum_array_elements(arr, num_integers);

    // Part 5: Print out the elements of the array from smallest to largest (ascending order) and which position they are in
    printf("\nPart 5:\n");
    print_sorted_array(arr, num_integers);

    // Part 6: Print out the elements of the array except the first and last element are swapped and the position they are in
    printf("\nPart 6:\n");
    print_swapped_first_last(arr, num_integers);

    return 0;
}

// Part 1: Print out the elements of the array and which position they are in
void print_array(const int arr[], int size) {
    printf("     Your array is: ");
    for (int i = 0; i < size; i++) {
        printf("[%d] = %d", i, arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
}

// Part 2: Print out the elements of the array in reverse order and which position they are in
void print_reverse_array(const int arr[], int size) {
    printf("     Your array in reverse is: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("[%d] = %d", i, arr[i]);
        if (i > 0) {
            printf(", ");
        }
    }
}

// Part 3: Print out all the even elements in the array and which position they are in
void print_even_elements(const int arr[], int size) {
    printf("     The even elements in the array is: ");
    int first_even = 1; // Flag to handle initial comma placement
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
}

// Part 4: Print out the sum of all values in the array
void sum_array_elements(const int arr[], int size) {
    long long sum = 0; // Use long long to prevent overflow for large sums
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    printf("     The sum of all values in your array is: %lld", sum);
}

// Part 5: Print out the elements of the array from smallest to largest (ascending order) and which position they are in
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

    // Sort the temporary array based on values using selection sort
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
}

// Part 6: Print out the elements of the array except the first and last element are swapped and the position they are in
void print_swapped_first_last(const int arr[], int size) {
    printf("     Your array with first and last element switched is: ");
    // Handle edge case where size is less than 2 and print accordingly using print_array
    if (size < 2) {
        print_array(arr, size);
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