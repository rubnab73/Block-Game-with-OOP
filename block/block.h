#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

using namespace std;

class Block
{
    int cellSize;
    int rotationState;
    int rowOffset;
    int columnOffset;
    vector<Color>colors;
public:
    int id;
    Block();
    void Draw(int offsetX,int offsetY);
    void Move(int rows,int columns);
    vector<Position> GetCellPosition();
    map<int,vector<Position>>cells;
    void Rotate();
    void UndoRotation();
};
