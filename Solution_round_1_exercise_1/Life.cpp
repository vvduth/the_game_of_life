#include"Life.h"

using namespace std;
int Life::neighbor_count(int row, int col) const 
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/

{
    int i, j;
    int count = 0;
    if (row > 0 && col > 0 && row < maxrow -1 && col < maxcol -1 ) {
        for (i = row - 1; i <= row + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;
    } //default
    else if (col == 0 && row > 0 && row < maxrow - 1) {  //col = 0
        for (i = row - 1; i <= row + 1; i++)
            for (j = col; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;

    } else if (col < maxcol - 1  && col > 0 && row == 0 ) { // row = 0
        for (i = row ; i <= row + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;

    } else if (col == maxcol -1 && row > 0 && row < maxrow - 1){ //col = hedge
        for (i = row - 1; i <= row + 1; i++)
            for (j = col - 1; j <= col ; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;
    }
    else if (row == maxrow - 1 && col > 0 && col < maxrow - 1) { //row = hedge
        for (i = row - 1; i <= row ; i++)
            for (j = col - 1; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;
    }
    else if (row == 0 && col == 0 ) { //both = 0
        for (i = row ; i <= row + 1; i++)
            for (j = col ; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;
    }
    else if (row == maxrow - 1 && col == maxcol - 1) { //both = hedge
        for (i = row-1; i <= row ; i++)
            for (j = col-1; j <= col ; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;
    }
    else if (row == 0 && col == maxcol - 1) { //row = 0 and col = hedge
        for (i = row ; i <= row + 1; i++)
            for (j = col - 1; j <= col; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;
    }
    else if (row == maxrow -1 && col == 0) { //row = hegde and col = 0
        for (i = row -1 ; i <= row ; i++)
            for (j = col ; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.


        return count;
    }
    
}

void Life::setMaxRow(int maxrow) {
    this->maxrow = maxrow;
}
void Life::setMaxCol(int maxcol) {
    this->maxcol = maxcol;
}
int Life::getMaxCol() {
    return maxcol;
}
int Life::getMaxRow() {
    return maxrow;
}

void  Life::update() const
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/

{
    int row, col;
    //int new_grid[maxrow + 2][maxcol + 2];
    int** new_grid = new int* [maxrow + 2];
    for (int i = 0; i < maxrow ; i++) {
        new_grid[i] = new int[maxcol];

    }

    for (row = 0; row < maxrow; row++)
        for (col = 0; col < maxcol; col++)
            switch (neighbor_count(row, col)) {
            case 2:
                new_grid[row][col] = grid[row][col];  //  Status stays the same.
                break;
            case 3:
                new_grid[row][col] = 1;                //  Cell is now alive.
                break;
            default:
                new_grid[row][col] = 0;                //  Cell is now dead.
            }

    for (row = 0; row < maxrow; row++)
        for (col = 0; col < maxcol; col++)
            grid[row][col] = new_grid[row][col];

    for (int i = 0; i < maxrow ; i++) {
        delete[] new_grid[i];
    }
    delete[] new_grid;
}



void  Life::initialize()
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{

    int row, col;
    grid = new int* [maxrow];
    for (int i = 0; i < maxrow ; i++) {
        grid[i] = new int[maxcol];

    }

    ifstream file{ "text.txt" };
    if (!file.is_open()) {};

    for (int i{}; i != maxrow; ++i) {
        for (int j{}; j != maxcol; ++j) {
            file >> grid[i][j];
        }
    }

    /*for (row = 0; row < maxrow; row++)
        for (col = 0; col < maxcol ; col++)
            grid[row][col] = 0;*/



    /*cout << "List the coordinates for living cells." << endl;
    cout << "Terminate the list with the special pair -1 -1" << endl;
    cin >> row >> col;

    while (row != -1 || col != -1) {
        if (row - 1 >= 0 && row - 1 <= maxrow)
            if (col - 1 >= 0 && col - 1 <= maxcol)
                grid[row - 1 ][col - 1] = 1;
            else
                cout << "Column " << col << " is out of range." << endl;
        else
            cout << "Row " << row << " is out of range." << endl;
        cin >> row >> col;
    }*/


}

void Life::exportToTxt()
{
    ofstream qfile("output.txt", ios_base::app);
    int row, col;
    cout << "\nThe current Life configuration is:" << endl;
    for (row = 0; row < maxrow; row++) {
        for (col = 0; col < maxcol; col++)
            if (grid[row][col] == 1) qfile << '*';
            else qfile << '.';
            //qfile << grid[row][col];
        qfile << endl;
    }
    qfile.close();
    cout << endl;
    


}


void Life::print() const 
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
    int row, col;
    cout << "\nThe current Life configuration is:" << endl;
    for (row = 0; row < maxrow; row++) {
        for (col = 0; col < maxcol; col++)
            if (grid[row][col] == 1) cout << '*';
            else cout << '.';
        cout << endl;
    }
    cout << endl;
    /*for (int i = 0; i < maxrow + 2; i++) {
        for (int j = 0; j < maxcol +2 ; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }*/
}

