#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 21
#define MAX_WORDS 100

int compare_strings_2d(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;
    char input_buffer[MAX_WORD_LENGTH];

    printf("Enter word: ");
    while (fgets(input_buffer, MAX_WORD_LENGTH, stdin) != NULL && input_buffer[0] != '\n') {
        input_buffer[strcspn(input_buffer, "\n")] = 0;

        if (num_words < MAX_WORDS) {
            strcpy(words[num_words], input_buffer);
            num_words++;
        } else {
            printf("Maximum number of words reached.\n");
            break;
        }
        printf("Enter word: ");
    }

    if (num_words == 0) {
        printf("No words entered.\n");
        return 0;
    }

    char first_word[MAX_WORD_LENGTH];
    char last_word[MAX_WORD_LENGTH];

    strcpy(first_word, words[0]);
    strcpy(last_word, words[0]);

    for (int i = 1; i < num_words; i++) {
        if (strcmp(words[i], first_word) < 0) {
            strcpy(first_word, words[i]);
        }
        if (strcmp(words[i], last_word) > 0) {
            strcpy(last_word, words[i]);
        }
    }

    printf("First: %s\n", first_word);
    printf("Last: %s\n", last_word);

    qsort(words, num_words, sizeof(words[0]), compare_strings_2d);

    printf("In sorted order: ");
    for (int i = 0; i < num_words; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    return 0;
}