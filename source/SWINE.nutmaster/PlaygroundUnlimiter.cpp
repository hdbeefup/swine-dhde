// PlaygroundUnlimiter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    std::cout << "Hello World!\n";

    /*
    std::cout << "============\n";
    std::cout << "RAW FILE READ\n";

    std::ifstream file("tanks.txt");
    std::string str;
    while (std::getline(file, str))
    {
        cout << str<<endl;
    }*/

    std::cout << "============\n";
    std::cout << "PROCESS TEXT\n";

    int i, characters = 0;
    std::string strDL;
    std::ifstream file("tanks.txt");
    std::string str2;
    while (std::getline(file, str2))
    {
        //check characters
        for (i = 0; str2[i] != '\0'; i++) {
            if (str2[i] != '\0') {
                characters++;
                //cout << str2[i] << " | " << characters<<endl;
            }
        }

        //std::cout << "============\n";
        /*cout << str2 << "| "<<characters;
        cout << endl;*/
        //characters = 0;

        /*std::cout << "============\n";
        std::cout << "\"Data Logistics\"\n";*/
        /* for loop, and something like php .= to add into variable current output*/

        // used in the same order as described above:
        strDL.append(str2);                       // "Writing "
        strDL.append((50 - characters), '.');                    // ".........."
        //strDL.append<int>((50-characters), "\0");                // "....."


        characters = 0;
    }

    std::cout << "============\n";
    std::cout << "USE OUTPUT AS SIMPLE VARIABLE\n";
    std::cout << strDL << '\n';
    //std::cout << " - not implemented - \n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
