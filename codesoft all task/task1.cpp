#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

int main() {
    // Initialize random seed
    std::srand(std::time(0)); // Seed the random number generator with the current time

    // Generate a random number between 1 and 100
    int number_to_guess = std::rand() % 100 + 1;

    int user_guess = 0;
    bool correct_guess = false;

    std::cout << "I have selected a number between 1 and 100. Try to guess it!" << std::endl;

    while (!correct_guess) {
        // Prompt user for their guess
        std::cout << "Enter your guess: ";
        std::cin >> user_guess;

        // Check if the guess is correct, too high, or too low
        if (user_guess < number_to_guess) {
            std::cout << "Too low! Try again." << std::endl;
        } else if (user_guess > number_to_guess) {
            std::cout << "Too high! Try again." << std::endl;
        } else {
            std::cout << "Congratulations! You've guessed the number correctly!" << std::endl;
            correct_guess = true; // Exit the loop
        }
    }

    return 0;
}
