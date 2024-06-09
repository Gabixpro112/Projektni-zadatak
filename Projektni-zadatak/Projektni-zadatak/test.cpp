#include <cstdlib> // For system()

int main()
{
    // Use system command to play the audio file on Windows
    system("start test.wav");

    return 0;
}
