/*
 * Program Name: converter.c
 * Purpose: Implements a simple unit converter for different measurements.
 * Author: Bruce 251368377
 * Date: October 7, 2025
 */

#include <stdio.h>

int main() {
    int choice;
    char conversion_direction;
    float value, result;

    do {
        printf("What do you want to do?\n");
        printf("1 - conversion between Grams and Ounces (1 gram == 0.03527 ounces)\n");
        printf("2 - conversion between Square meters and Square Yards (1 square meter == 1.19599 square yards)\n");
        printf("3 - conversion between Litres and Pints (1 litre == 2.11338 pints)\n");
        printf("4 - conversion between Meter and Feet (1 meter == 3.28084 feet)\n");
        printf("5 - quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Grams and Ounces
                printf("G - conversion from Grams to Ounces\n");
                printf("O - conversion from Ounces to Grams\n");
                printf("Enter your choice (G/O): ");
                // Consume the newline character left by previous scanf
                while ((getchar()) != '\n'); 
                scanf("%c", &conversion_direction);

                if (conversion_direction == 'G' || conversion_direction == 'g') {
                    printf("Please enter a value in Grams: ");
                    scanf("%f", &value);
                    result = value * 0.03527;
                    printf("Your conversion is %.2f Ounces\n", result);
                } else if (conversion_direction == 'O' || conversion_direction == 'o') {
                    printf("Please enter a value in Ounces: ");
                    scanf("%f", &value);
                    result = value / 0.03527;
                    printf("Your conversion is %.2f Grams\n", result);
                } else {
                    printf("Invalid conversion direction. Please try again.\n");
                }
                break;
            case 2: // Square meters and Square Yards
                printf("M - conversion from Square Meters to Square Yards\n");
                printf("Y - conversion from Square Yards to Square Meters\n");
                printf("Enter your choice (M/Y): ");
                while ((getchar()) != '\n');
                scanf("%c", &conversion_direction);

                if (conversion_direction == 'M' || conversion_direction == 'm') {
                    printf("Please enter a value in Square Meters: ");
                    scanf("%f", &value);
                    result = value * 1.19599;
                    printf("Your conversion is %.2f Square Yards\n", result);
                } else if (conversion_direction == 'Y' || conversion_direction == 'y') {
                    printf("Please enter a value in Square Yards: ");
                    scanf("%f", &value);
                    result = value / 1.19599;
                    printf("Your conversion is %.2f Square Meters\n", result);
                } else {
                    printf("Invalid conversion direction. Please try again.\n");
                }
                break;
            case 3: // Litres and Pints
                printf("L - conversion from Litres to Pints\n");
                printf("P - conversion from Pints to Litres\n");
                printf("Enter your choice (L/P): ");
                while ((getchar()) != '\n');
                scanf("%c", &conversion_direction);

                if (conversion_direction == 'L' || conversion_direction == 'l') {
                    printf("Please enter a value in Litres: ");
                    scanf("%f", &value);
                    result = value * 2.11338;
                    printf("Your conversion is %.2f Pints\n", result);
                } else if (conversion_direction == 'P' || conversion_direction == 'p') {
                    printf("Please enter a value in Pints: ");
                    scanf("%f", &value);
                    result = value / 2.11338;
                    printf("Your conversion is %.2f Litres\n", result);
                } else {
                    printf("Invalid conversion direction. Please try again.\n");
                }
                break;
            case 4: // Meter and Feet
                printf("M - conversion from Meters to Feet\n");
                printf("F - conversion from Feet to Meters\n");
                printf("Enter your choice (M/F): ");
                while ((getchar()) != '\n');
                scanf("%c", &conversion_direction);

                if (conversion_direction == 'M' || conversion_direction == 'm') {
                    printf("Please enter a value in Meters: ");
                    scanf("%f", &value);
                    result = value * 3.28084;
                    printf("Your conversion is %.2f Feet\n", result);
                } else if (conversion_direction == 'F' || conversion_direction == 'f') {
                    printf("Please enter a value in Feet: ");
                    scanf("%f", &value);
                    result = value / 3.28084;
                    printf("Your conversion is %.2f Meters\n", result);
                } else {
                    printf("Invalid conversion direction. Please try again.\n");
                }
                break;
            case 5: // Quit
                printf("Exiting converter. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n"); // Add a newline for better readability between menu iterations
    } while (choice != 5);

    return 0;
}