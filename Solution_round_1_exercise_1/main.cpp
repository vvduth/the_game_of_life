#include "utility.h"
#include "life.h"

#include<string>
using namespace std;


class Timer {
    std::atomic<bool> active{ true };

public:
    void setTimeout(void(*func)(), int delay);
    void setInterval(Life obj, int interval) {
        active = true;
        std::thread t([=]() {
            while (active.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if (!active.load()) return;
                obj.update();
                obj.print();
            }
            });
        t.detach();
    };
    void stop();

};

void Timer::setTimeout(void (*func)(), int delay) {
    active = true;
    std::thread t([=]() {
        if (!active.load()) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (!active.load()) return;
        func();

        });
    t.detach();
}




void Timer::stop() {
    active = false;
}

int setUpGrid(int a) {

    //std::string filename;
    //cout << "Enter filename" << " "; cin >> filename;

    std::string line_;
    ifstream file_("text2.txt");
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

string setUpGrid2(int a) {

    ifstream file_("text.txt");
    string dummyLine;
    string dummLine2;
    string line_;
    getline(file_, dummyLine);
    getline(file_, dummLine2);
    // Begin reading your stream here
    //while (file_);
    if (file_.is_open()) {
        while (getline(file_, line_)) {
            cout << line_<< '\n';
        }
        file_.close();
    }
    else {
        cout << "wrong";
    }
    return line_;
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
    Timer t;
    int a, b;
    cout << "Welcome to Conway's game of Life." << endl;
    
    /*cout << "Please enter max row: "; cin >> a; cout << endl;
    cout << "Please enter max col: "; cin >> b; cout << endl;*/
    //setUpGrid2(1); cout << endl;
    //cout << setUpGrid2(1);
    Life configuration(setUpGrid(0),setUpGrid(1));
    instructions(configuration,setUpGrid(0),setUpGrid(1));
    configuration.initialize();
    configuration.print();
    cout << "Continue viewing new generations? " << endl;
    while (user_says_yes()) {

        t.setInterval(configuration, 3000);
        //configuration.update();
        //configuration.print();
        
        //cout << "Continue viewing new generations? " << endl;
    }

    
    configuration.exportToTxt();
    
}
