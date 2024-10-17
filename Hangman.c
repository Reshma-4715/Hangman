#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Constants for the game
#define MAX_ATTEMPTS 6    // Maximum number of wrong guesses
#define WORD_SIZE 100      // Maximum word size

// Function prototypes
void displayWord(char word[], int wordLength, int guessed[]);
int isWordGuessed(int guessed[], int wordLength);
char toLower(char c);

int main() {
    char word[WORD_SIZE];          // Secret word to guess
    char display[WORD_SIZE];       // Displayed word with blanks
    int guessed[WORD_SIZE] = {0};  // Track guessed letters (0 or 1 for each)
    int attempts = 0;              // Incorrect guesses counter
    int wordLength;                // Length of the word
    char guess;                    // Player's letter guess

    printf("Enter the word to be guessed (hidden from the player): ");
    scanf("%s", word);             // Input the word to guess
    wordLength = strlen(word);

    // Clear the console to hide the word from the player
    printf("\033[2J\033[1;1H");  // ANSI escape sequence to clear screen

    printf("Welcome to Hangman!\n");

    // Main game loop
    while (attempts < MAX_ATTEMPTS) {
        displayWord(word, wordLength, guessed);

        printf("\n\nEnter your guess: ");
        scanf(" %c", &guess);
        guess = toLower(guess);  // Convert to lowercase for consistency

        // Check if the guessed letter is in the word
        int correct = 0;
        for (int i = 0; i < wordLength; i++) {
            if (toLower(word[i]) == guess) {
                guessed[i] = 1;  // Mark this letter as guessed
                correct = 1;
            }
        }

        if (!correct) {
            attempts++;
            printf("Incorrect guess! Attempts remaining: %d\n", 
                   MAX_ATTEMPTS - attempts);
        }

        if (isWordGuessed(guessed, wordLength)) {
            printf("\nCongratulations! You've guessed the word: %s\n", word);
            return 0;
        }
    }

    printf("\nGame over! You've run out of attempts. The word was: %s\n", word);
    return 0;
}

// Function to display the word with blanks for unguessed letters
void displayWord(char word[], int wordLength, int guessed[]) {
    printf("Word: ");
    for (int i = 0; i < wordLength; i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Function to check if the entire word has been guessed
int isWordGuessed(int guessed[], int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        if (!guessed[i]) {
            return 0;  // If any letter is not guessed, return false
        }
    }
    return 1;  // All letters guessed
}

// Function to convert a character to lowercase
char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}
