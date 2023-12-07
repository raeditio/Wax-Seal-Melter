#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char getUserChoice() {
    char choice[2]; // Store a character and null terminator
    char input[100]; // Buffer for user input

    fgets(input, sizeof(input), stdin);

    // Check if the input buffer contains a newline character
    if (input[0] != '\n') {
        sscanf(input, "%1s", choice); // Extract the user input value
    } else {
        choice[0] = '\0'; // Set choice to empty string if only newline was entered
    }

    return choice[0];
}

// Function to get user input for a double value
bool getUserInput(char *result) {
    char input[100]; // Buffer for user input

    fgets(input, sizeof(input), stdin);

    // Check if the input buffer contains a newline character
    if (input[0] != '\n') {
        sscanf(input, "%s", result); // Extract the input as a double
		return true; // input is valid double
    } else {
        result[0] = '\0'; // Set choice to empty string if only newline was entered
		return false; // input is not valid double
    }
}