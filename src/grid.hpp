#pragma once 
#include<vector>
using namespace std;


class Grid
{
    public:
        Grid(int width, int height , int cellSize)
        : rows(height / cellSize), columns(width / cellSize), cellSize(cellSize), cells(rows, vector<int>(columns, 0)) {};
        void Draw();
        void SetValue(int row, int column, int value);
    private:
        int rows;
        int columns;
        int cellSize;
        vector<vector<int>> cells; 



};

