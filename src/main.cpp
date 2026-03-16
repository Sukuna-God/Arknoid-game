#include<iostream>
#include<raylib.h>
using namespace std;

class Ball{
public:
    float ballX;
    float ballY;
    float ballR;
    Color ballC;

    Ball(float x, float y, float r, Color c){
        ballX = x;
        ballY = y;
        ballR = r;
        ballC = c;
    }

    void Draw(){
        DrawCircle(ballX, ballY, ballR, YELLOW);
    }

};

class Paddle{
public:
    float X;
    float Y;
    float H;
    float W;
    Color C;
    Rectangle rec = {};

    void Draw(){
        DrawRectangleRec(rec, C);
    }
};


Paddle paddle;

int main(){
    InitWindow(800, 600, "Window");
    SetTargetFPS(60);

    Ball ball = Ball(400.0f, 300.0f, 10.0f, LIME);

    paddle.X = 350.0f;
    paddle.Y = 450.0f;
    paddle.H = 30.0f;
    paddle.W = 120.0f;
    paddle.C = RED;
    paddle.rec = {paddle.X, paddle.Y, paddle.W, paddle.H};

    float spX = 4;
    float spY = 4;

    bool gameLose = false;

    bool active[42];

    Rectangle recs[42] = {
        {50, 50, 90, 30},
        {145, 50, 90, 30},
        {240, 50, 90, 30},
        {335, 50, 90, 30},
        {430, 50, 90, 30},
        {525, 50, 90, 30},
        {620, 50, 90, 30},

        {50, 85, 90, 30},
        {145, 85, 90, 30},
        {240, 85, 90, 30},
        {335, 85, 90, 30},
        {430, 85, 90, 30},
        {525, 85, 90, 30},
        {620, 85, 90, 30},

        {50, 120, 90, 30},
        {145, 120, 90, 30},
        {240, 120, 90, 30},
        {335, 120, 90, 30},
        {430, 120, 90, 30},
        {525, 120, 90, 30},
        {620, 120, 90, 30},

        {50, 155, 90, 30},
        {145, 155, 90, 30},
        {240, 155, 90, 30},
        {335, 155, 90, 30},
        {430, 155, 90, 30},
        {525, 155, 90, 30},
        {620, 155, 90, 30},

        {50, 190, 90, 30},
        {145, 190, 90, 30},
        {240, 190, 90, 30},
        {335, 190, 90, 30},
        {430, 190, 90, 30},
        {525, 190, 90, 30},
        {620, 190, 90, 30},

        {50, 225, 90, 30},
        {145, 225, 90, 30},
        {240, 225, 90, 30},
        {335, 225, 90, 30},
        {430, 225, 90, 30},
        {525, 225, 90, 30},
        {620, 225, 90, 30},
    };

    for(int i=0; i < 42; i++){
        active[i] = true;
    }

    while(!WindowShouldClose()){

        if(!gameLose){
            if(paddle.X > 0 &&IsKeyDown(KEY_A)){
                paddle.X -= 10;
                paddle.rec = {paddle.X, paddle.Y, paddle.W, paddle.H};
            }
            if(paddle.X <= 700 && IsKeyDown(KEY_D)){
                paddle.X += 10;
                paddle.rec = {paddle.X, paddle.Y, paddle.W, paddle.H};
            }
        }

        if(gameLose && IsKeyDown(KEY_R)){
            ball.ballX = 400.0f;
            ball.ballY = 300.0f;

            paddle.X = 350.0f;
            paddle.Y = 450.0f;

            gameLose = false;
        }
         
        if(CheckCollisionCircleRec({ball.ballX, ball.ballY}, ball.ballR, Rectangle{paddle.X, paddle.Y, paddle.W, paddle.H})){
            spY *= -1;
        }

        if((ball.ballX + ball.ballR) >= 800 || (ball.ballX + ball.ballR) <= 20){
            spX *= -1;
        }

        if((ball.ballY + ball.ballR) <= 20){
            spY *= -1;
        }

        if(ball.ballY > 600){
            DrawText("You loss press R for restart", 250, 280, 20, BLACK);
            gameLose = true;
        }

        for(int i=0; i < 42; i++){
            if(active[i] && CheckCollisionCircleRec({ball.ballX, ball.ballY}, ball.ballR, recs[i])){
                active[i] = false;
                spY*=-1;
            }
        }

        

        ball.ballX += spX;
        ball.ballY += spY;

        BeginDrawing();

        ClearBackground({99,149,238});
        ball.Draw();
        paddle.Draw();
        
        for(int i=0; i < 42; i++){
            if(active[i]){
                DrawRectangleRec(recs[i], LIME);
            }
            
        }   

        EndDrawing();
    }

    CloseWindow();
    return 0;
}