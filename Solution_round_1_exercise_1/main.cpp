#include "utility.h"
#include "life.h"
#include<fstream>
#include<string>
using namespace std;

int setUpGrid(int a) {

    //std::string filename;
    //cout << "Enter filename" << " "; cin >> filename;

    std::string line_;
    ifstream file_("text.txt");
    int number;
    std::string text;
    int number2;

    int the_line_I_care_about = a;  // holds the line number you are searching for
    int current_line = 0;          // 0-based. First line is "0", second is "1", etc.
    while (std::getline(file_, text))     // NEVER say 'f.eof()' as a loop condition
    {
        if (current_line == the_line_I_care_about) {
            // We have reached our target line
            //std::cout << text;            // Display the target line
            break;                     // Exit loop so we only print ONE line, not many
        }
        current_line++;              // We haven't found our line yet, so repeat.
    }
    file_.close();

    /* if (file_.is_open()) {
         while (file_ >> number >> text >> number2) {
             cout << number << " " << " " << number2 << " " << '\n';
          }





         file_.close();
     }
     else {
         cout << "wrong";
     }*/
    return std::stoi(text);
}


void instructions(Life obj, int a , int b)
/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/

{   
    
    obj.setMaxRow(a);
    obj.setMaxCol(b);
    cout << "This game uses a grid of size "
        << obj.getMaxRow() << " by " << obj.getMaxCol() << " in which" << endl;
    cout << "each cell can either be occupied by an organism or not." << endl;
    cout << "The occupied cells change from generation to generation" << endl;
    cout << "according to the number of neighboring cells which are alive."
        << endl;
}


int main()  //  Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

{
    /*int a, b;
    cout << "Welcome to Conway's game of Life." << endl;
    cout << "Please enter max row: "; cin >> a; cout << endl;
    cout << "Please enter max col: "; cin >> b; cout << endl;*/
    Life configuration(setUpGrid(0),setUpGrid(1));
    instructions(configuration,setUpGrid(0),setUpGrid(1));
    configuration.initialize();
    configuration.print();
    cout << "Continue viewing new generations? " << endl;
    while (user_says_yes()) {
        configuration.update();
        configuration.print();
        cout << "Continue viewing new generations? " << endl;
    }
}
