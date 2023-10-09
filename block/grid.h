#pragma once
#include <vector>
#include "raylib.h"

using namespace std;
class Grid
{
public:
    Grid();
    void initialize();
    void Print();
    void Draw();
    int grid[20][30];
    bool IsCellOutside(int row,int column);
    int ClearFullRows();
    bool IsCellEmpty(int row, int column);

private:
    int numRows;
    int numCols;
    int cellSize;
    vector<Color>colors;
    bool isRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
};
