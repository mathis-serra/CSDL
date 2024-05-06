#include<vector>
#include<utility>
#include "simulation.hpp"
using namespace std;


void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value) 
{
    grid.SetValue(row, column, value);
}


int Simulation::CountLiveNeighbors(int row, int column)
{   
    int liveNeighbors = 0;
    vector<pair<int, int>> neighborOffsets =
    {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0 , 1},
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };

    for(const auto& offset : neighborOffsets){
        int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighborColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns(); 
        liveNeighbors += grid.GetValue(neighborRow, neighborColumn);
    }
    return liveNeighbors;
}

void Simulation::Update()
{
    for(int row = 0; row < grid.GetRows(); row++){
        for(int column = 0; column < grid.GetColumns(); column++){
            int liveNeighbors = CountLiveNeighbors(row, column);
            int cellValue = grid.GetValue(row, column);


            if( cellValue == 1){
                if (liveNeighbors > 3 || liveNeighbors < 2) {
                    grid.SetValue(row, column, 0);
                }

                else
                {
                    tempGrid.SetValue(row, column, 1);
                }
            }
            else 
            {
                if(liveNeighbors == 3)
                {
                    tempGrid.SetValue(row, column, 1);
                }
                else
                {
                    tempGrid.SetValue(row, column, 0);
                }
            }
        }
    }
    grid = tempGrid;
}
