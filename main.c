#include <raylib.h>
#include <string.h>
#include <time.h>

#define SEED 4124215
#define WINDOW_WID 1280
#define WINDOW_HEI 960
#define BOX_WID 40
#define BOX_HEI 40
#define GRID_WID WINDOW_WID / BOX_WID
#define GRID_HEI WINDOW_HEI / BOX_HEI

void starting_grid(int grid[GRID_WID][GRID_HEI])
{
    //glider
    // grid[1][2] = 1;
    // grid[2][3] = 1;
    // grid[3][1] = 1;
    // grid[3][2] = 1;
    // grid[3][3] = 1;

    //blinker
    // grid[1][2] = 1;
    // grid[2][2] = 1;
    // grid[3][2] = 1;

    //beacon
    // grid[1][1] = 1;
    // grid[1][2] = 1;
    // grid[2][1] = 1;
    // grid[4][3] = 1;
    // grid[4][4] = 1;
    // grid[3][4] = 1;

    // RANDOM
    for(int i = 0 ; i < GRID_WID ; i++) {
        for(int j = 0 ; j < GRID_HEI ; j++) {
            grid[i][j] = (rand() + SEED) % 2;
        }
    }
}

void DrawMyGrid(int grid[GRID_WID][GRID_HEI])
{
    for(int i = 0 ; i < GRID_WID; i++) {
        for(int j = 0 ; j < GRID_HEI ; j++) {
            if(grid[i][j] == 1) {
                DrawRectangle(i*BOX_WID , j*BOX_HEI , BOX_WID , BOX_HEI ,RAYWHITE);
            }
        }
    }
}

int CalculatePopulation(int grid[GRID_WID][GRID_HEI] , int x , int y)
{
    int population = 0;
    //left
    if(x - 1 >= 0) {
        population += grid[x-1][y] == 1 ? 1 : 0;
    }
    //right
    if(x + 1 < GRID_WID) {
        population += grid[x+1][y] == 1 ? 1 : 0;
    }
    //up
    if(y - 1 >= 0) {
        population += grid[x][y-1] == 1 ? 1 : 0;
    }
    //down
    if(y + 1 < GRID_HEI) {
        population += grid[x][y+1] == 1 ? 1 : 0;
    }
    //up left
    if(x - 1 >= 0 && y - 1 >= 0) {
        population += grid[x-1][y-1] == 1 ? 1 : 0;
    }
    //up right
    if(x + 1 < GRID_WID && y - 1 >= 0) {
        population += grid[x+1][y-1] == 1 ? 1 : 0;
    }
    //down left
    if(x - 1 >= 0 && y + 1 < GRID_HEI) {
        population += grid[x-1][y+1] == 1 ? 1 : 0;
    }
    //down right
    if(x + 1 < GRID_WID && y + 1 < GRID_HEI) {
        population += grid[x+1][y+1] == 1 ? 1 : 0;
    }

    return population;
}

void FindNextGrid(int grid[GRID_WID][GRID_HEI], int nextGrid[GRID_WID][GRID_HEI])
{
    for(int i = 0; i < GRID_WID ; i++ ){
        for(int j = 0 ; j < GRID_HEI ; j++) {
            int Population = CalculatePopulation(grid , i , j);
            if(Population < 2 || Population > 3) {
                nextGrid[i][j] = 0;
            }
            else if(Population == 3) {
                nextGrid[i][j] = 1;
            }
            else {
                nextGrid[i][j] = grid[i][j];
            }
        }
    }
}

void MyConwaysGame(int grid[GRID_WID][GRID_HEI], int nextGrid[GRID_WID][GRID_HEI])
{
    DrawMyGrid(grid);
    FindNextGrid(grid , nextGrid); 
}

int main()
{
    srand(time(NULL));
    int grid[GRID_WID][GRID_HEI];
    int nextGrid[GRID_WID][GRID_HEI];
    memset(grid , 0 , sizeof(grid));
    starting_grid(grid);

    InitWindow(WINDOW_WID , WINDOW_HEI , "Conway's Game of Life");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        SetTargetFPS(5);
        MyConwaysGame(grid , nextGrid);
        memcpy(grid, nextGrid, sizeof(grid));
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
