#include <iostream>
#include <stdlib.h>
#include "raylib.h"
#include "game.h"
#include <fstream>
using namespace std;

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

template<typename T>
T difficulty()
{
    cout<<"=================="<<endl;
    cout<<"Select Difficulty"<<endl;
    cout<<"1.Easy"<<endl;
    cout<<"2.Medium"<<endl;
    cout<<"3.Hard"<<endl;
    cout<<"=================="<<endl;
    int choice;
    T speed;
    cin>>choice;
    switch(choice)
    {
    case 1:
        speed = 0.7;
        break;
    case 2:
        speed = 0.5;
        break;
    case 3:
        speed = 0.3;
        break;
    default:
        break;
    }
    return speed;
}

int main()
{
    float speed = difficulty<float>();
    Color darkbeguni = {73,40,73,255};
    InitWindow(700,620,"Nabil's Block game");
    SetTargetFPS(60);
    Font font = LoadFontEx("Font/MachineGunk-nyqg.ttf",64,0,0);
    Texture2D atlas = LoadTexture("Images/Game-Over-PNG-Image.png");
    Game game;
    ifstream in("highscore.txt");
    string prevscore;
    in >> prevscore;
    int readscore = stoi(prevscore);
    in.close();
    while(!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if(EventTriggered(speed))
        {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkbeguni);
        DrawTextEx(font,"SCORE",{465,15},38,2,WHITE);
        DrawTextEx(font,"NEXT",{475,170},38,2,WHITE);
        if(game.gameOver)
        {
            PauseMusicStream(game.music);
            DrawTextureEx(atlas,(Vector2){420,450},0,0.3f,WHITE);
        }
        DrawRectangleRounded({403,60,220,60},0.3,6,RED);
        char scoreText[10];
        sprintf(scoreText,"%d",game.score);
        Vector2 textSize= MeasureTextEx(font,scoreText,38,2);
        DrawTextEx(font,scoreText,{425+(170-textSize.x)/2,65},38,2,WHITE);
        DrawRectangleRounded({403,215,220,180},0.3,6,WHITE);
        game.Draw();
        EndDrawing();
        if(readscore<game.score)
        {
            readscore = game.score;
        }
        char highscore[10];
        sprintf(highscore,"HIGH SCORE IS %d",readscore);
        DrawTextEx(font,highscore,{450,590},16,2,WHITE);

    }
    CloseWindow();
    ofstream file;
    file.open("highscore.txt");
    file << readscore;
    file.close();
    return 0;
}
