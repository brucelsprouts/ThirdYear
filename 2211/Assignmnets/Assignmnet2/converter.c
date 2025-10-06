#include <stdio.h>
#include <stdbool.h>

int main () {
    int user_in;
    bool valid_in;

    while(valid) {
        printf("What would you liek to do? (int)\n
            1 - For conversion between Grams and Ounces\n
            2 - For conversion betweeen Square meters and Square Yards\n
            3 - For conversion between Litres and Pints\n
            4 - For conversion between Meter and Feet\n
            5 - Quit\n");

        scanf("%d", &user_in);

        if (user_in != 1,2,3,4,5) {
            printf("Invalid input, try again")
        } else {
            valid = FALSE
        }
    }
    

    switch(user_in) {
        case 1: 
        case 2: 
        case 3: 
        case 4: 
        case 5: 
        default: 
    }

}