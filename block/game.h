#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <iostream>
using namespace std;

class Game
{
    vector <Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    void LockBlock();
    void RotateBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared,int moveDownPoints);
    Block GetRandomBlock();
    vector<Block>GetAllBlocks();
    void MoveBlockRight();
    void MoveBlockLeft();
    Sound clearSound;
    Sound rotateSound;
public:
    Game();
    Grid grid;
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;
    Music music;
    ~Game();
    friend float difficulty(Game);
};


