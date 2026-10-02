#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

// ------------------------------------------------------------
// WORD GUESS GAME
// DSA / C++ Console Project
// ------------------------------------------------------------

// Displays the main title.
void displayTitle() {
    cout << "\n";
    cout << "============================================================\n";
    cout << "                    WORD GUESS CHALLENGE\n";
    cout << "============================================================\n";
    cout << "Guess the hidden word one letter at a time!\n";
    cout << "You have a limited number of chances, so choose wisely.\n";
    cout << "Type EXIT at any time to leave the game.\n";
    cout << "============================================================\n\n";
}

// Displays the available categories.
void displayCategories() {
    cout << "Choose a category:\n";
    cout << "  1. Animals\n";
    cout << "  2. Teams\n";
    cout << "  3. Districts\n";
    cout << "  4. Films\n";
    cout << "  5. Books\n";
    cout << "  0. Exit\n";
    cout << "\nEnter your choice: ";
}

// Returns the category name.
string getCategoryName(int category) {
    switch (category) {
        case 1: return "Animals";
        case 2: return "Teams";
        case 3: return "Districts";
        case 4: return "Films";
        case 5: return "Books";
        default: return "Unknown";
    }
}

// Converts a string to lowercase.
string toLowerCase(string text) {
    for (char &ch : text) {
        ch = static_cast<char>(
            tolower(static_cast<unsigned char>(ch))
        );
    }

    return text;
}

// Checks whether the user's input is EXIT.
bool isExitCommand(const string &input) {
    return toLowerCase(input) == "exit";
}

// Checks whether a string contains only one alphabetic letter.
bool isSingleLetter(const string &input) {
    return input.length() == 1 &&
           isalpha(static_cast<unsigned char>(input[0]));
}

// Displays the word with guessed letters revealed.
void displayProgress(const string &word, const string &guessedLetters) {
    cout << "\nWord: ";

    bool allRevealed = true;

    for (char letter : word) {
        char lowerLetter =
            static_cast<char>(
                tolower(static_cast<unsigned char>(letter))
            );

        if (lowerLetter == ' ') {
            cout << "  ";
        }
        else if (guessedLetters.find(lowerLetter) != string::npos) {
            cout << lowerLetter << ' ';
        }
        else {
            cout << "_ ";
            allRevealed = false;
        }
    }

    cout << "\n";
}

// Checks whether the entire word has been guessed.
bool isWordComplete(
    const string &word,
    const string &guessedLetters
) {
    for (char letter : word) {

        if (letter == ' ') {
            continue;
        }

        char lowerLetter =
            static_cast<char>(
                tolower(static_cast<unsigned char>(letter))
            );

        if (guessedLetters.find(lowerLetter) == string::npos) {
            return false;
        }
    }

    return true;
}

// Checks whether a letter occurs in the word.
bool containsLetter(const string &word, char letter) {

    letter = static_cast<char>(
        tolower(static_cast<unsigned char>(letter))
    );

    for (char wordLetter : word) {

        if (static_cast<char>(
                tolower(static_cast<unsigned char>(wordLetter))
            ) == letter) {

            return true;
        }
    }

    return false;
}

// Displays the letters already guessed.
void displayGuessedLetters(const string &guessedLetters) {

    cout << "Guessed letters: ";

    if (guessedLetters.empty()) {
        cout << "None";
    }
    else {

        for (char letter : guessedLetters) {

            cout << static_cast<char>(
                toupper(static_cast<unsigned char>(letter))
            ) << ' ';
        }
    }

    cout << "\n";
}

// Gives a small hint without revealing the whole word.
void giveHint(
    const string &word,
    const string &guessedLetters
) {

    for (char letter : word) {

        if (letter == ' ') {
            continue;
        }

        char lowerLetter =
            static_cast<char>(
                tolower(static_cast<unsigned char>(letter))
            );

        if (guessedLetters.find(lowerLetter) == string::npos) {

            cout << "Hint: The word contains the letter '"
                 << static_cast<char>(
                        toupper(
                            static_cast<unsigned char>(lowerLetter)
                        )
                    )
                 << "'.\n";

            return;
        }
    }
}

// Selects a random word from the chosen category.
string selectRandomWord(int category) {

    // Different word categories stored in vectors.
    const vector<string> animals = {
        "elephant",
        "giraffe",
        "kangaroo",
        "dolphin",
        "penguin",
        "crocodile",
        "butterfly",
        "cheetah"
    };

    const vector<string> teams = {
        "arsenal",
        "barcelona",
        "chelsea",
        "liverpool",
        "rayon sports",
        "manchester city",
        "real madrid"
    };

    const vector<string> districts = {
        "gasabo",
        "kicukiro",
        "nyarugenge",
        "musanze",
        "huye",
        "rubavu",
        "rwamagana",
        "nyagatare"
    };

    const vector<string> films = {
        "inception",
        "avatar",
        "titanic",
        "interstellar",
        "frozen",
        "coco",
        "moana",
        "gladiator"
    };

    const vector<string> books = {
        "hamlet",
        "macbeth",
        "matilda",
        "dune",
        "dracula",
        "pinocchio",
        "oliver twist",
        "the hobbit"
    };

    // Pointer used to refer to the selected category.
    const vector<string>* selectedCategory = nullptr;

    switch (category) {

        case 1:
            selectedCategory = &animals;
            break;

        case 2:
            selectedCategory = &teams;
            break;

        case 3:
            selectedCategory = &districts;
            break;

        case 4:
            selectedCategory = &films;
            break;

        case 5:
            selectedCategory = &books;
            break;

        default:
            return "";
    }

    // Generate a random index.
    int index = rand() % selectedCategory->size();

    // Return the word at that random index.
    return (*selectedCategory)[index];
}

// Plays one complete round.
bool playRound(int category, int &score) {

    string word = selectRandomWord(category);
    string guessedLetters;

    // The number of chances is equal to the number
    // of alphabetic characters in the selected word.
    int MAX_CHANCES = 0;

    for (char letter : word) {
        if (isalpha(static_cast<unsigned char>(letter))) {
            MAX_CHANCES++;
        }
    }

    int chancesLeft = MAX_CHANCES;
    int wrongGuesses = 0;

    bool hintUsed = false;

    cout << "\n------------------------------------------------------------\n";
    cout << "Category: " << getCategoryName(category) << "\n";
    cout << "You have " << MAX_CHANCES << " chances.\n";
    cout << "Type HINT if you need help.\n";
    cout << "------------------------------------------------------------\n";

    while (chancesLeft > 0) {

        displayProgress(word, guessedLetters);
        displayGuessedLetters(guessedLetters);

        cout << "Chances left: " << chancesLeft << "\n";
        cout << "Enter a letter, HINT, or EXIT: ";

        string input;
        cin >> input;

        // Convert the command to lowercase.
        string command = toLowerCase(input);

        // EXIT command.
        if (command == "exit") {

            cout << "\nYou chose to exit the game. Goodbye!\n";

            return false;
        }

        // HINT command.
        if (command == "hint") {

            if (!hintUsed) {

                giveHint(word, guessedLetters);
                hintUsed = true;
            }
            else {

                cout << "You have already used your hint for this round.\n";
            }

            continue;
        }

        // The game accepts exactly one alphabetic character.
        if (!isSingleLetter(input)) {

            cout << "Invalid input. Please enter ONE letter.\n";

            continue;
        }

        // Convert the guessed letter to lowercase.
        char guess = static_cast<char>(
            tolower(static_cast<unsigned char>(input[0]))
        );

        // Prevent duplicate guesses.
        if (guessedLetters.find(guess) != string::npos) {

            cout << "You already guessed '"
                 << guess
                 << "'. Try another letter.\n";

            continue;
        }

        // Store the guessed letter.
        guessedLetters += guess;

        // Check whether the letter exists.
        if (containsLetter(word, guess)) {

            cout << "Correct! '"
                 << guess
                 << "' is in the word!\n";

            // Check if the complete word has been guessed.
            if (isWordComplete(word, guessedLetters)) {

                cout << "\n****************************************************\n";
                cout << "                 YOU WON!!!\n";
                cout << "****************************************************\n";

                cout << "The word was: "
                     << word
                     << "\n";

                // More points for solving with more chances remaining.
                int roundScore =
                    100 +
                    (chancesLeft * 10) -
                    (hintUsed ? 15 : 0);

                score += roundScore;

                cout << "Round score: "
                     << roundScore
                     << "\n";

                cout << "Total score: "
                     << score
                     << "\n";

                return true;
            }
        }
        else {

            wrongGuesses++;
            chancesLeft--;

            cout << "Sorry! '"
                 << guess
                 << "' is not in the word.\n";
        }
    }

    // Player used all chances.
    cout << "\n****************************************************\n";
    cout << "                 GAME OVER!\n";
    cout << "****************************************************\n";

    cout << "The word was: "
         << word
         << "\n";

    cout << "Wrong guesses: "
         << wrongGuesses
         << "\n";

    cout << "Total score: "
         << score
         << "\n";

    return true;
}

// Asks the player whether another round should begin.
bool playAgain() {

    while (true) {

        cout << "\nDo you want to play again? (Y/N): ";

        string answer;
        cin >> answer;

        if (answer.length() == 1) {

            char choice = static_cast<char>(
                tolower(static_cast<unsigned char>(answer[0]))
            );

            if (choice == 'y') {
                return true;
            }

            if (choice == 'n') {
                return false;
            }
        }

        cout << "Please enter Y or N.\n";
    }
}

int main() {

    // Seed the random number generator once.
    srand(
        static_cast<unsigned int>(
            time(nullptr)
        )
    );

    int totalScore = 0;
    bool running = true;

    displayTitle();

    while (running) {

        displayCategories();

        /*
           Read the category as a string first.

           This prevents inputs such as:
           1-5
           12
           -1
           2abc

           from being partially interpreted as valid numbers.
        */
        string categoryInput;
        cin >> categoryInput;

        // Input must contain exactly one character.
        if (categoryInput.length() != 1 ||
            categoryInput[0] < '0' ||
            categoryInput[0] > '5') {

            cout << "\nInvalid input. "
                 << "Please choose a number from 1 to 5, "
                 << "or 0 to exit.\n";

            continue;
        }

        // Convert the character '0'...'5' to integer 0...5.
        int category = categoryInput[0] - '0';

        // Exit option.
        if (category == 0) {

            cout << "\nThank you for playing Word Guess Challenge!\n";

            break;
        }

        // Play the selected category.
        bool roundFinished =
            playRound(category, totalScore);

        // EXIT from inside the round.
        if (!roundFinished) {
            break;
        }

        // Ask whether the player wants another round.
        if (!playAgain()) {

            cout << "\nFinal score: "
                 << totalScore
                 << "\n";

            cout << "Thanks for playing! Goodbye!\n";

            running = false;
        }
    }

    return 0;
}