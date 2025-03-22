#include <stdio.h>
#include "raylib.h"

int player_score = 0;   // Initialise player score
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
void UpdatePlayerPaddle(struct Paddle *);  // Function for player paddle when local multiplayer is disabled
void UpdatePlayer1Paddle(struct Paddle *); // Function for player1 paddle when local multiplayer is enabled
void UpdatePlayer2Paddle(struct Paddle *); // Function for player2 paddle when local multiplayer is enabled
void UpdateComputerPaddle(struct Paddle *, struct Ball *);
void DrawBall(struct Ball *);
void DrawPlayerPaddle(struct Paddle *);
void DrawComputerPaddle(struct Paddle *);
void ResetBall(struct Ball *);

typedef enum GameScreen
{
    TITLE = 0,
    GAMEPLAY
} GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    const int screen_width = 1280;
    const int screen_height = 800;
    printf("Starting the game...");

    InitWindow(screen_width, screen_height, "Raycong: A Pong Game!"); // Initialize window and OpenGL context
    SetTargetFPS(60);                                                 // Set target FPS (maximum)

    Texture2D start_button = LoadTexture("resources/button_rectangle_depth_border.png");
    Texture2D check_box = LoadTexture("resources/check_square_grey.png");
    Texture2D check_box_clicked = LoadTexture("resources/check_square_grey_square.png");
    Texture2D radio_button = LoadTexture("resources/check_round_grey.png");
    Texture2D radio_button_clicked = LoadTexture("resources/check_round_grey_circle.png");

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

    GameScreen current_screen = TITLE;
    Rectangle start_button_bounds = {(screen_width / 2.0f - start_button.width / 2.0f), (screen_height / 2.5f - start_button.height / 2.0f), (float)start_button.width, (float)start_button.height};
    Rectangle localmultiplayer_button_bounds = {(screen_width / 2.0f - start_button.width / 1.4f), (screen_height / 2.0f), (float)check_box.width, (float)check_box.height};
    Rectangle endless_game_button_bounds = {(screen_width / 2.0f - start_button.width / 1.4f), (screen_height / 1.7f), (float)check_box.width, (float)check_box.height};
    Rectangle relaxed_button_bounds = {(screen_width / 2.0f - start_button.width / 0.9f), (screen_height / 1.3f), (float)radio_button.width, (float)radio_button.height};
    Rectangle fast_button_bounds = {(screen_width / 2.0f - start_button.width / 3.5f), (screen_height / 1.3f), (float)radio_button.width, (float)radio_button.height};
    Rectangle lightning_button_bounds = {(screen_width / 2.0f + start_button.width / 3.0f), (screen_height / 1.3f), (float)radio_button.width, (float)radio_button.height};
    Vector2 mouse_point = {0.0f, 0.0f}; // Initialise mouse point at (0, 0)
    bool is_mouse_over_start_button = false;
    bool is_mouse_over_localmultiplyaer_button = false;
    bool is_mouse_over_endless_game_button = false;
    bool is_mouse_over_relaxed_button = false;
    bool is_mouse_over_fast_button = false;
    bool is_mouse_over_lightning_button = false;
    Texture2D localmultiplayer_button_state = check_box;
    Texture2D endless_game_button_state = check_box;
    Texture2D relaxed_button_state = radio_button_clicked;
    Texture2D fast_button_state = radio_button;
    Texture2D lightning_button_state = radio_button;

    // Game Loop
    while (WindowShouldClose() == false)
    {
        mouse_point = GetMousePosition();
        is_mouse_over_start_button = CheckCollisionPointRec(mouse_point, start_button_bounds);
        is_mouse_over_localmultiplyaer_button = CheckCollisionPointRec(mouse_point, localmultiplayer_button_bounds);
        is_mouse_over_endless_game_button = CheckCollisionPointRec(mouse_point, endless_game_button_bounds);
        is_mouse_over_relaxed_button = CheckCollisionPointRec(mouse_point, relaxed_button_bounds);
        is_mouse_over_fast_button = CheckCollisionPointRec(mouse_point, fast_button_bounds);
        is_mouse_over_lightning_button = CheckCollisionPointRec(mouse_point, lightning_button_bounds);

        switch (current_screen)
        {
        case TITLE:
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            // Logic for PLAY button
            if (is_mouse_over_start_button)
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

                // Check if PLAY button pressed
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_screen = GAMEPLAY;
                }
            }

            // Logic for Local Multiplayer button
            if (is_mouse_over_localmultiplyaer_button)
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

                if (localmultiplayer_button_state.id == check_box.id && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    localmultiplayer_button_state = check_box_clicked;
                }
                else if (localmultiplayer_button_state.id == check_box_clicked.id && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    localmultiplayer_button_state = check_box;
                }
            }

            // Logic for Endless Game button
            if (is_mouse_over_endless_game_button)
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

                if (endless_game_button_state.id == check_box.id && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    endless_game_button_state = check_box_clicked;
                }
                else if (endless_game_button_state.id == check_box_clicked.id && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    endless_game_button_state = check_box;
                }
            }

            // Logic for Relaxed button
            if (is_mouse_over_relaxed_button)
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

                if (relaxed_button_state.id == radio_button.id && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    relaxed_button_state = radio_button_clicked;
                    fast_button_state = radio_button;
                    lightning_button_state = radio_button;
                }
            }

            // Logic for Fast button
            if (is_mouse_over_fast_button)
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

                if (fast_button_state.id == radio_button.id && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    fast_button_state = radio_button_clicked;
                    relaxed_button_state = radio_button;
                    lightning_button_state = radio_button;
                }
            }

            // Logic for Lightning button
            if (is_mouse_over_lightning_button)
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

                if (lightning_button_state.id == radio_button.id && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    lightning_button_state = radio_button_clicked;
                    relaxed_button_state = radio_button;
                    fast_button_state = radio_button;
                }
            }

            // Logic for changing speed of the ball and paddle based on game pace
            if (relaxed_button_state.id == radio_button_clicked.id)
            {
                ball.speed_x = -7;
                ball.speed_y = -7;
                player.speed = 6;
                computer.speed = 6;
            }
            else if (fast_button_state.id == radio_button_clicked.id)
            {
                ball.speed_x = -10;
                ball.speed_y = -10;
                player.speed = 8;
                computer.speed = 8;
            }
            else if (lightning_button_state.id == radio_button_clicked.id)
            {
                ball.speed_x = -13;
                ball.speed_y = -13;
                player.speed = 10;
                computer.speed = 10;
            }

            if (IsKeyPressed(KEY_SPACE))
            {
                current_screen = GAMEPLAY;
            }
            break;
        case GAMEPLAY:
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            // Press P to pause the game
            if (IsKeyPressed(KEY_P))
            {
                current_screen = TITLE;
            }

            if (endless_game_button_state.id != check_box_clicked.id)
            {
                if (player_score == 10 || computer_score == 10)
                {
                    current_screen = TITLE;
                    player_score = 0;
                    computer_score = 0;
                }
            }
            break;
        }

        BeginDrawing(); // Setup canvas (framebuffer) to start drawing

        switch (current_screen)
        {
        case TITLE:
            DrawText("Raycong", 300, 10, 150, RAYWHITE);

            DrawTexture(start_button, (screen_width / 2.0f - start_button.width / 2.0f), (screen_height / 2.5f - start_button.height / 2.0f), RAYWHITE);
            DrawText("PLAY", (screen_width / 2.0f - start_button.width / 2.0f) + 40, (screen_height / 2.5f - start_button.height / 2.0f) + 10, 85, BLACK);

            DrawTexture(localmultiplayer_button_state, (screen_width / 2.0f - start_button.width / 1.4f), (screen_height / 2.0f) + 10, RAYWHITE);
            DrawText("Local Multiplayer", (screen_width / 2.0f - start_button.width / 1.4f) + 60, (screen_height / 2.0f) + 15, 40, RAYWHITE);

            DrawTexture(endless_game_button_state, (screen_width / 2.0f - start_button.width / 1.4f), (screen_height / 1.7f) + 10, RAYWHITE);
            DrawText("Endless Game", (screen_width / 2.0f - start_button.width / 1.4f) + 60, (screen_height / 1.7f) + 15, 40, RAYWHITE);

            DrawText("Game Pace", (screen_width / 2.0f - start_button.width / 3.0f), (screen_height / 1.4f), 40, RAYWHITE);

            DrawText("Relaxed", (screen_width / 2.0f - start_button.width / 0.9f) + 60, (screen_height / 1.3f) + 15, 40, RAYWHITE);
            DrawTexture(relaxed_button_state, (screen_width / 2.0f - start_button.width / 0.9f), (screen_height / 1.3f) + 10, RAYWHITE);

            DrawText("Fast", (screen_width / 2.0f - start_button.width / 3.5f) + 60, (screen_height / 1.3f) + 15, 40, RAYWHITE);
            DrawTexture(fast_button_state, (screen_width / 2.0f - start_button.width / 3.5f), (screen_height / 1.3f) + 10, RAYWHITE);

            DrawText("Lightning", (screen_width / 2.0f + start_button.width / 3.0f) + 60, (screen_height / 1.3f) + 15, 40, RAYWHITE);
            DrawTexture(lightning_button_state, (screen_width / 2.0f + start_button.width / 3.0f), (screen_height / 1.3f) + 10, RAYWHITE);

            ClearBackground(SKYBLUE);

            break;
        case GAMEPLAY:
            // Updating
            UpdateBall(&ball);

            // Check if local multiplayer is enabled
            if (localmultiplayer_button_state.id == check_box_clicked.id)
            {
                UpdatePlayer1Paddle(&computer);
                UpdatePlayer2Paddle(&player);
            }
            else
            {
                UpdatePlayerPaddle(&player);
                UpdateComputerPaddle(&computer, &ball);
            }

            // Collision detection
            if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius, (Rectangle){player.x, player.y, player.width, player.height}))
                ball.speed_x *= -1;
            if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius, (Rectangle){computer.x, computer.y, computer.width, computer.height}))
                ball.speed_x *= -1;

            // Drawing
            ClearBackground(Blue);
            DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Dark_Blue);
            DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Blue);
            DrawBall(&ball); // Same as "DrawCircle(ball.x, ball.y, ball.radius, RAYWHITE);"
            DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, RAYWHITE);
            DrawPlayerPaddle(&player);     // Same as "DrawRectangle(1245, (screen_height / 2 - 60), 25, 120, RAYWHITE);"
            DrawComputerPaddle(&computer); // Same as "DrawRectangle(10, (screen_height / 2 - 60), 25, 120, RAYWHITE);"
            DrawText(TextFormat("%d", computer_score), screen_width / 4 - 20, 20, 80, RAYWHITE);
            DrawText(TextFormat("%d", player_score), ((3 * screen_width) / 4) - 20, 20, 80, RAYWHITE);
            break;
        }

        EndDrawing(); // End canvas drawing and swap buffers (double buffering)
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // Unload textures from GPU memory (VRAM)
    UnloadTexture(start_button);
    UnloadTexture(check_box);
    UnloadTexture(check_box_clicked);
    UnloadTexture(radio_button);
    UnloadTexture(radio_button_clicked);

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

void UpdatePlayer1Paddle(struct Paddle *c)
{
    // Move the Paddle
    if (IsKeyDown(KEY_W))
        c->y -= c->speed;
    if (IsKeyDown(KEY_S))
        c->y += c->speed;

    // Limit movement
    if (c->y <= 0)
        c->y = 0;
    if (c->y + c->height >= GetScreenHeight())
        c->y = GetScreenHeight() - c->height;
}

void UpdatePlayer2Paddle(struct Paddle *p)
{
    // Move the Paddle
    if (IsKeyDown(KEY_UP))
        p->y -= p->speed;
    if (IsKeyDown(KEY_DOWN))
        p->y += p->speed;

    // Limit movement
    if (p->y <= 0)
        p->y = 0;
    if (p->y + p->height >= GetScreenHeight())
        p->y = GetScreenHeight() - p->height;
}

void UpdateComputerPaddle(struct Paddle *c, struct Ball *b)
{
    // Move the Paddle
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

void ResetBall(struct Ball *b)
{
    b->x = GetScreenHeight() / 2.0;
    b->y = GetScreenWidth() / 2.0;

    int speed_choice[2] = {-1, 1};
    b->speed_x *= speed_choice[GetRandomValue(0, 1)];
    b->speed_y *= speed_choice[GetRandomValue(0, 1)];
}