#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0)); // Initialize random number generator.

    string keys[4] = {"w", "a", "s", "d"};
    string randomString;
    int randomLength = rand() % 7 + 4; // Generate a random length between 4 and 10.

    // Generate a random string of WASD keys.
    for (int i = 0; i < randomLength; ++i)
    {
        randomString += keys[rand() % 4];
        if (i != randomLength - 1)
        {
            randomString += " ";
        }
    }

    cout << "Random string: " << randomString << endl;

    string userInput;
    int index = 0;

    while (index < randomString.size())
    {
        cout << "Enter the next key: ";
        getline(cin, userInput);

        string currentKey = randomString.substr(index, userInput.size());

        if (userInput == currentKey)
        {
            index += userInput.size() + 1;
        }
        else
        {
            cout << "Wrong key! Starting over..." << endl;
            index = 0;
        }
    }

    cout << "Congratulations! You entered the string correctly." << endl;

    return 0;
}
