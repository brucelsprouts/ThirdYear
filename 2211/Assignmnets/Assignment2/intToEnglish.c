/*
 * Program Name: intToEnglish.c
 * Purpose: Translates integers from 1-999 into English words.
 * Author: Bruce 251368377
 * Date: October 7, 2025
 */

#include <stdio.h>
#include <string.h>

// Function to convert a number to its English word equivalent
void convertToEnglish(int num) {
    char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    if (num == 0) {
        printf("zero");
        return;
    }

    if (num >= 100) {
        printf("%s hundred", ones[num / 100]);
        num %= 100;
        if (num > 0) {
            printf(" and ");
        }
    }

    if (num >= 20) {
        printf("%s", tens[num / 10]);
        num %= 10;
        if (num > 0) {
            printf("-");
        }
    } else if (num >= 11 && num <= 19) {
        printf("%s", teens[num - 10]);
        num = 0; // Handled teens, no need for ones digit
    } else if (num == 10) {
        printf("ten");
        num = 0;
    }

    if (num > 0) {
        printf("%s", ones[num]);
    }
}

int main() {
    int input_value;

    do {
        printf("Please enter a value (1-999, 0 to quit): ");
        scanf("%d", &input_value);

        if (input_value == 0) {
            printf("Exiting intToEnglish. Goodbye!\n");
        } else if (input_value >= 1 && input_value <= 999) {
            printf("You entered the number ");
            convertToEnglish(input_value);
            printf("\n");
        } else {
            printf("Invalid input. Please enter a value between 1 and 999, or 0 to quit.\n");
        }
        printf("\n"); // Add a newline for better readability
    } while (input_value != 0);

    return 0;
}