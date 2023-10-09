#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("sound/background.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("sound/rotate.wav");
    clearSound = LoadSound("sound/clear.wav");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector <Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11,11);
    nextBlock.Draw(365, 275);
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0,1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if(!gameOver)
    {
        currentBlock.Move(0,-1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0,1);
        }
    }
}

void Game::MoveBlockRight()
{
    if(!gameOver)
    {
        currentBlock.Move(0,1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0,-1);
        }
    }
}
void Game::MoveBlockDown()
{
    if(!gameOver)
    {
        currentBlock.Move(1,0);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item:tiles)
    {
        if(grid.IsCellOutside(item.row,item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if(!gameOver)
    {
        currentBlock.Rotate();
        if(IsBlockOutside())
        {
            currentBlock.UndoRotation();
        }
        else PlaySound(rotateSound);
    }
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits()==false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if(rowsCleared>0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared,0);
    }
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles)
    {
        if(grid.IsCellEmpty(item.row,item.column)==false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    PlayMusicStream(music);
    grid.initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared,int moveDownPoints)
{
    switch(linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 1000;
        break;
    case 5:
        score += 1500;
        break;
    default:
        break;
    }
    score += moveDownPoints;
}

