#pragma once
#include<fstream>
#include<string>
#include<iostream>
#include"timercpp.h"
using namespace std;
//const int maxrow = 20, maxcol = 60;    //  grid dimensions


class Life {
public:
	void initialize();
	void print() const;
	void update() const ;
	void setMaxRow(int maxrow);
	void setMaxCol(int maxcol);
	int getMaxRow();
	int getMaxCol();
	void exportToTxt();
	
	Life(int maxrow, int maxcol){
		this->maxrow = maxrow;
		this->maxcol = maxcol;
		
	}
	~Life() {
		
	}
private:
	//int grid[maxrow + 2][maxcol + 2];  //  allows for two extra rows and columns
	int neighbor_count(int row, int col) const ;
	int maxrow;
	int maxcol;
	int** grid;
};




