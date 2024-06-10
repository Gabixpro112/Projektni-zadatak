
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <conio.h>
#include <mutex>
#include <vector>
#include <algorithm>
#include <condition_variable>
#include <cstdlib>
using namespace std;

bool timeUp = false;   // Global flag to indicate if the time is up
mutex mtx;             // Mutex to protect shared resources
condition_variable cv; // Condition variable for the countdown
int remainingTime;     // Remaining time for the countdown

void countdown()
{
    unique_lock<mutex> lock(mtx);
    while (remainingTime > 0)
    {
        cv.wait_for(lock, std::chrono::seconds(1));
        --remainingTime;

        if (remainingTime <= 0)
        {
            timeUp = true;
            break;
        }
    }
    cout << "\rTime's up!                \n"; // Extra spaces to overwrite the previous output
}

void addTime(int seconds)
{
    lock_guard<mutex> lock(mtx);
    remainingTime += seconds;
    cv.notify_all(); // Notify the countdown thread
}

void saveScore(const string &playerName, int score)
{
    ofstream outFile("rezultat.bin", ios::binary | ios::app);
    if (!outFile)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    size_t nameLength = playerName.size();
    outFile.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
    outFile.write(playerName.c_str(), nameLength);
    outFile.write(reinterpret_cast<const char *>(&score), sizeof(score));
    outFile.close();
}

vector<pair<string, int>> loadScores()
{
    vector<pair<string, int>> scores;
    ifstream inFile("rezultat.bin", ios::binary);
    if (!inFile)
    {
        cerr << "Error opening file for reading." << endl;
        return scores;
    }

    while (inFile)
    {
        size_t nameLength;
        inFile.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
        if (inFile.eof())
            break;

        string playerName(nameLength, '\0');
        inFile.read(&playerName[0], nameLength);

        int score;
        inFile.read(reinterpret_cast<char *>(&score), sizeof(score));

        scores.emplace_back(playerName, score);
    }

    inFile.close();
    return scores;
}

void displayLeaderboard()
{
    vector<pair<string, int>> scores = loadScores();
    if (scores.empty())
    {
        cout << "No scores available." << endl;
        return;
    }

    // Sort scores in descending order
    sort(scores.begin(), scores.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { return a.second > b.second; });

    cout << "Leaderboard:" << endl;
    for (const auto &entry : scores)
    {
        cout << entry.first << ": " << entry.second << endl;
    }
}

void deleteAllScores()
{
    ofstream outFile("rezultat.bin", ios::binary | ios::trunc);
    if (!outFile)
    {
        cerr << "Error opening file for truncating." << endl;
    }
    outFile.close();
    cout << "All scores deleted." << endl;
}

int main()
{
    int unos;

    while (true)
    {
        cout << "stratagemhero" << endl;
        cout << "1. New game" << endl;
        cout << "2. Leaderboard" << endl;
        cout << "3. Delete all score data" << endl;
        cout << "4. Exit" << endl;
        cout << "Unesite svoj unos" << endl;
        cin >> unos;

        if (unos == 1)
        {
            string playerName;
            cout << "Unesite svoje ime" << endl;
            cin >> playerName;
            ofstream outFile("players.txt", ios::app);
            outFile << playerName << endl;
            outFile.close();
            cout << "Hit all the keys in the correct order" << endl;
            int rezultat = -5;
            srand(time(0)); // Initialize random number generator.
            const char keys[] = {'w', 'a', 's', 'd'};

            // Start the countdown in a separate thread
            timeUp = false;
            remainingTime = 20; // Initial time for the countdown
            thread countdownThread(countdown);
            countdownThread.detach(); // Detach the countdown thread from the main thread

            int runda = 1;
            while (true)
            {
                {
                    lock_guard<mutex> lock(mtx);
                    if (timeUp)
                        break; // Break the loop if the time is up
                }

                string randomString;
                int randomLength = rand() % 7 + 4; // Generate a random length between 4 and 10.

                // Generate a random string of WASD keys.
                for (int i = 0; i < randomLength; ++i)
                {
                    randomString += keys[rand() % 4];
                }

                cout << "Round " << runda << ": " << randomString << endl;

                int index = 0;
                bool mistakeMade = false;

                while (index < randomString.size())
                {
                    {
                        lock_guard<mutex> lock(mtx);
                        if (timeUp)
                            break; // Break the loop if the time is up
                    }

                    char ch = _getch(); // Read a character without waiting for Enter

                    if (ch == randomString[index])
                    {
                        cout << ch;
                        ++index; // Increment the index only when the correct key is pressed
                    }
                    else
                    {
                        mistakeMade = true;
                        index = 0;
                        cout << "\n\n";
                        cout << "Round " << runda << ": " << randomString << endl;
                    }
                }

                if (!mistakeMade)
                {
                    rezultat += 5; // Bonus points for no mistakes
                }

                cout << "\nRound done" << endl;
                rezultat += 5;
                ++runda;
                addTime(2); // Add 2 seconds for each round completed
            }

            cout << "Game over! Your final score is: " << rezultat << endl;
            saveScore(playerName, rezultat);
        }
        else if (unos == 2)
        {
            displayLeaderboard();
        }
        else if (unos == 3)
        {
            deleteAllScores();
        }
        else if (unos == 4)
        {
            cout << "Exiting program." << endl;
            break;
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
