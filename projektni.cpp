#include <iostream>
#include <thread>
#include <chrono>
#include <random>
using namespace std;

int main()
{
    char keys[] = {'W', 'A', 'S', 'D'};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 3); // Randomly choose 0, 1, 2, or 3
    uniform_int_distribution<> lengthDis(4, 10);

    int totalScore = 0;
    const int MAX_TIME_SECONDS = 10; // Set the maximum time in seconds

    while (true)
    {
        int sequenceLength = lengthDis(gen);

        // Print the randomly generated sequence
        cout << "Random sequence: ";
        for (int i = 0; i < sequenceLength; ++i)
        {
            int randomIndex = dis(gen); // Moved inside the loop
            cout << keys[randomIndex] << " ";
        }
        cout << endl;

        // Get user input
        cout << "Enter your sequence (W, A, S, D): ";
        string userInput;
        cin >> userInput;

        // Check user input against the generated sequence
        int score = 0;
        for (int i = 0; i < sequenceLength; ++i)
        {
            if (i >= userInput.length() || userInput[i] != keys[randomIndex])
            { // Fixed randomIndex usage
                cout << "Invalid input or timeout. Timer expired!" << endl;
                return 0;
            }
            ++score;
        }

        // Extend the timer based on user input
        this_thread::sleep_for(chrono::seconds(2)); // Extend timer by 2 seconds
        cout << "Timer extended!" << endl;
        cout << "Your score for this sequence: " << score << "/" << sequenceLength << endl;
        totalScore += score;

        // Check if the total time has exceeded the maximum allowed time
        if (totalScore >= MAX_TIME_SECONDS)
        {
            cout << "Time's up! Total score: " << totalScore << endl;
            break; // Exit the loop
        }
    }

    return 0;
}
