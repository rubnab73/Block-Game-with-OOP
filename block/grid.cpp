#include <iostream>
#include "grid.h"
#include "colors.h"
using namespace std;

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    initialize();
    colors = GetCellColors();
}
void Grid::initialize()
{
    for(int row=0;row<numRows;row++)
    {
        for(int column=0;column<numCols;column++)
        {
            grid[row][column]=0;
        }
    }
}
void Grid::Print()
{
    for(int row=0;row<numRows;row++)
    {
        for(int column=0;column<numCols;column++)
        {
            cout<<grid[row][column]<<" ";
        }
        cout<<endl;
    }
}

void Grid::Draw()
{
    for(int row=0;row<numRows;row++)
    {
        for(int column=0;column<numCols;column++)
        {
            int cellValue=grid[row][column];
            DrawRectangle(column*cellSize+11,row*cellSize+11,cellSize-1,cellSize-1,colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row,int column)
{
    if(row >= 0 && row < numRows && column >= 0 && column < numCols){
        return false;
    }
    else return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if(grid[row][column]==0)
    {
        return true;
    }
    else return false;
}

bool Grid::isRowFull(int row)
{
    for(int column = 0; column < numCols; column++)
    {
        if(grid[row][column]==0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int column = 0;column < numCols;column++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for(int column = 0;column < numCols;column++)
    {
        grid[row+numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row = numRows -1 ; row>=0 ;row--)
    {
        if(isRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if(completed>0)
        {
            MoveRowDown(row,completed);
        }
    }
    return completed;
}
