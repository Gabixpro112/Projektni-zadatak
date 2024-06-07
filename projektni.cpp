#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
void countdown(int seconds) // timer za igru treba unjeti countdown(start_time);
{
    while (seconds > 0)
    {
        std::cout << "\rTime remaining: " << seconds << " seconds" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --seconds;
    }
    std::cout << "\rTime's up!                \n"; // Extra spaces to overwrite the previous output
}
int main()
{
    int runda, rezultat,unos,ime;
    int start_time = 20;
    runda = 1;
    rezultat = 0;
    cout << "stratagemhero" << endl;
    cout << "1.New game" << endl;
    cout << "2.lederbourdgh" << endl;
    cout << "3.Delete all score data" << endl;
    cout << "Unesite svoj unos" << endl;
    cin >> unos;
    if(unos==1)
    {
        cout << "Unesite svoje ime" << endl;
        cin >> ime;
        
    }
}
