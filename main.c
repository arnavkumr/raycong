#include <stdio.h>
#include "raylib.h"

int player_score = 0; // Initialise player score
int computer_score = 0; // Initialise computer score

Color Dark_Blue = (Color){0, 153, 255, 255};
Color Blue = (Color){51, 173, 255, 255};
Color Light_Blue = (Color){128, 204, 255, 255};

// Define Ball structure to store ball properties
struct Ball
{
    float x, y; // Ball co-ordinates
    int speed_x, speed_y;
    int radius;
};

// Define Paddle structure to store paddle properties
struct Paddle
{
    float x, y; // Paddle co-ordinates
    float width, height;
    int speed;
};

// Function prototypes
void UpdateBall(struct Ball *);
void UpdatePlayerPaddle(struct Paddle *);
void UpdateComputerPaddle(struct Paddle *, struct Ball *);
void DrawBall(struct Ball *);
void DrawPlayerPaddle(struct Paddle *);
void DrawComputerPaddle(struct Paddle *);
void ResetBall(struct Ball *);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    const int screen_width = 1280;
    const int screen_height = 800;
    printf("Starting the game...");

    InitWindow(screen_width, screen_height, "Raycong: A Pong Game!"); // Initialize window and OpenGL context
    SetTargetFPS(60);                                // Set target FPS (maximum)

    struct Ball ball; // Create an instance named ball of the struct Ball

    // Define properties of the ball
    ball.radius = 15;
    ball.x = screen_width / 2.0;
    ball.y = screen_height / 2.0;
    ball.speed_x = -10;
    ball.speed_y = -10;

    struct Paddle player; // Create an instance named player of the struct Paddle

    // Define Properties of the player paddle
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 8;

    struct Paddle computer; // Create an instance named computer of the struct Paddle

    // Define Properties of the computer paddle
    computer.width = 25;
    computer.height = 120;
    computer.x = 10;
    computer.y = screen_height / 2 - computer.height / 2;
    computer.speed = 8;

    // Game Loop
    while (WindowShouldClose() == false)
    {
        BeginDrawing(); // Setup canvas (framebuffer) to start drawing

        // Updating
        UpdateBall(&ball);
        UpdatePlayerPaddle(&player);
        UpdateComputerPaddle(&computer, &ball);

        // Collision detection
        if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius, (Rectangle){player.x, player.y, player.width, player.height}))
            ball.speed_x *= -1;
        if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius, (Rectangle){computer.x, computer.y, computer.width, computer.height}))
            ball.speed_x *= -1;

        // Drawing
        ClearBackground(Blue);
        DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, Dark_Blue);
        DrawCircle(screen_width/2, screen_height/2, 150, Light_Blue);
        DrawBall(&ball); // Same as "DrawCircle(ball.x, ball.y, ball.radius, RAYWHITE);"
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, RAYWHITE);
        DrawPlayerPaddle(&player);     // Same as "DrawRectangle(1245, (screen_height / 2 - 60), 25, 120, RAYWHITE);"
        DrawComputerPaddle(&computer); // Same as "DrawRectangle(10, (screen_height / 2 - 60), 25, 120, RAYWHITE);"
        DrawText(TextFormat("%d", computer_score), screen_width/4 - 20, 20, 80, RAYWHITE);
        DrawText(TextFormat("%d", player_score), ((3*screen_width)/4) - 20, 20, 80, RAYWHITE);

        EndDrawing(); // End canvas drawing and swap buffers (double buffering)
    }

    CloseWindow(); // Close window and unload OpenGL context
    return 0;
}

void UpdateBall(struct Ball *b)
{
    // Move the ball
    b->x += b->speed_x;
    b->y += b->speed_y;

    // Collision detection
    if (b->y + b->radius >= GetScreenHeight() || b->y - b->radius <= 0)
    {
        b->speed_y *= -1;
    }
    if (b->x + b->radius >= GetScreenWidth())
    {
        computer_score++; // Computer wins a point
        ResetBall(b);
    }
    if (b->x - b->radius <= 0)
    {
        player_score++; // Player wins a point
        ResetBall(b);
    }
}

void UpdatePlayerPaddle(struct Paddle *p)
{
    // Move the Paddle
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        p->y -= p->speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        p->y += p->speed;

    // Limit movement
    if (p->y <= 0)
        p->y = 0;
    if (p->y + p->height >= GetScreenHeight())
        p->y = GetScreenHeight() - p->height;
}

void UpdateComputerPaddle(struct Paddle *c, struct Ball *b)
{
    if (c->y + c->height / 2 > b->y)
        c->y -= c->speed;
    if (c->y + c->height / 2 < b->y)
        c->y += c->speed;

    // Limit movement
    if (c->y <= 0)
        c->y = 0;
    if (c->y + c->height >= GetScreenHeight())
        c->y = GetScreenHeight() - c->height;
}

void DrawBall(struct Ball *b)
{
    DrawCircle(b->x, b->y, b->radius, DARKBLUE);
}

void DrawPlayerPaddle(struct Paddle *p)
{
    DrawRectangleRounded((Rectangle){p->x, p->y, p->width, p->height}, 0.8, 0, WHITE);
}

void DrawComputerPaddle(struct Paddle *c)
{
    DrawRectangleRounded((Rectangle){c->x, c->y, c->width, c->height}, 0.8, 0, WHITE);
}

void ResetBall(struct Ball *b) {
    b->x = GetScreenHeight()/2.0;
    b->y = GetScreenWidth()/2.0;

    int speed_choice[2] = {-1, 1};
    b->speed_x *= speed_choice[GetRandomValue(0, 1)];
    b->speed_y *= speed_choice[GetRandomValue(0, 1)];
}