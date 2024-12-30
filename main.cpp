#include <iostream>
#include <SDL2/SDL.h>

/* #include "Vector3.hpp"
#include "Matrix3.hpp" */

#include "math/Vector.hpp"
#include "math/Matrix.hpp"

#define X_SCALE 1
#define Y_SCALE 2
#define Z_SCALE 1

#define X_ROTATION M_PI / 4
#define Y_ROTATION M_PI / 3
#define Z_ROTATION 0

#define X_SCALE_S 0
#define Y_SCALE_S 0
#define Z_SCALE_S 0

#define X_ROTATION_S 0
#define Y_ROTATION_S 0
#define Z_ROTATION_S 0

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 90
#define SCREEN_TITLE "3D Projection"

#define BACKGROUND_COLOR 0, 0, 0, 255
#define EDGE_COLOR 255, 192, 203, 255

typedef Vector<3> Vector3;
typedef Matrix<3, 3> Matrix3;

int main(int argc, char **argv)
{
    Vector3 vertices[] = {
        Vector3({1, 1, 1}),
        Vector3({1, -1, 1}),
        Vector3({-1, -1, 1}),
        Vector3({-1, 1, 1}),
        Vector3({1, 1, -1}),
        Vector3({1, -1, -1}),
        Vector3({-1, -1, -1}),
        Vector3({-1, 1, -1})};

    {
        // set up the cube to the starting position defined
        // by the X_ROTATION, Y_ROTATION and Z_ROTATION
        // and the scale defined by the X_SCALE, Y_SCALE and Z_SCALE

        double scaleMatrix[3][3] = {
            {X_SCALE, 0, 0},
            {0, Y_SCALE, 0},
            {0, 0, Z_SCALE}};

        Matrix3 scaleMatrixM(scaleMatrix);
        for (int i = 0; i < 8; i++)
        {
            // scale the cube by the scale matrix
            vertices[i] = scaleMatrixM * vertices[i];
        }

        // --- rotation matrix
        double xRotationMatrix[3][3] = {
            {1, 0, 0},
            {0, cos(X_ROTATION), -sin(X_ROTATION)},
            {0, sin(X_ROTATION), cos(X_ROTATION)}};

        double yRotationMatrix[3][3] = {
            {cos(Y_ROTATION), 0, sin(Y_ROTATION)},
            {0, 1, 0},
            {-sin(Y_ROTATION), 0, cos(Y_ROTATION)}};

        double zRotationMatrix[3][3] = {
            {cos(Z_ROTATION), -sin(Z_ROTATION), 0},
            {sin(Z_ROTATION), cos(Z_ROTATION), 0},
            {0, 0, 1}};

        Matrix3 xRotationMatrixM(xRotationMatrix);
        Matrix3 yRotationMatrixM(yRotationMatrix);
        Matrix3 zRotationMatrixM(zRotationMatrix);

        Matrix3 rotationMatrix = xRotationMatrixM * yRotationMatrixM * zRotationMatrixM;

        /* multiply_matrix(xRotationMatrix, yRotationMatrix, result);
        multiply_matrix(result, zRotationMatrix, rotationMatrix); */

        for (int i = 0; i < 8; i++)
        {
            /* vertices[i] = vertices[i].matrixMultiplication(rotationMatrix); */
            vertices[i] = rotationMatrix * vertices[i];
        }

        // ---
    }

    // we made the projection of the cube on the plane z = 0
    // now we can draw the cube on the screen
    // we will use SDL2 to draw the cube on the screen

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window *win = SDL_CreateWindow(SCREEN_TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (win == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (ren == nullptr)
    {
        SDL_DestroyWindow(win);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // do a render loop
    // Event loop

    SDL_Event event;
    bool quit = false;

    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
        lastTime = currentTime;

        // Example: Print delta time
        // std::cout << "Delta Time: " << deltaTime << " seconds\n"
        //          << "FPS: " << 1 / deltaTime << std::endl; // rendering
        // set the color to black
        SDL_SetRenderDrawColor(ren, BACKGROUND_COLOR);
        SDL_RenderClear(ren);

        // lets do a projection on a plane with normal (0, 0, 1)
        double scaleMatrix[3][3] = {
            {X_SCALE_S * deltaTime + 1, 0, 0},
            {0, Y_SCALE_S * deltaTime + 1, 0},
            {0, 0, Z_SCALE_S * deltaTime + 1}};

        Matrix3 scaleMatrixM(scaleMatrix);

        double xRotationMatrix[3][3] = {
            {1, 0, 0},
            {0, cos(X_ROTATION_S * deltaTime), -sin(X_ROTATION_S * deltaTime)},
            {0, sin(X_ROTATION_S * deltaTime), cos(X_ROTATION_S * deltaTime)}};

        double yRotationMatrix[3][3] = {
            {cos(Y_ROTATION_S * deltaTime), 0, sin(Y_ROTATION_S * deltaTime)},
            {0, 1, 0},
            {-sin(Y_ROTATION_S * deltaTime), 0, cos(Y_ROTATION_S * deltaTime)}};

        double zRotationMatrix[3][3] = {
            {cos(Z_ROTATION_S * deltaTime), -sin(Z_ROTATION_S * deltaTime), 0},
            {sin(Z_ROTATION_S * deltaTime), cos(Z_ROTATION_S * deltaTime), 0},
            {0, 0, 1}};

        Matrix3 xRotationMatrixM(xRotationMatrix);
        Matrix3 yRotationMatrixM(yRotationMatrix);
        Matrix3 zRotationMatrixM(zRotationMatrix);

        Matrix3 rotationMatrix = xRotationMatrixM * yRotationMatrixM * zRotationMatrixM;

        /* multiply_matrix(xRotationMatrix, yRotationMatrix, result);
        multiply_matrix(result, zRotationMatrix, rotationMatrix); */

        for (int i = 0; i < 8; i++)
        {
            /* vertices[i] = vertices[i]
                              .matrixMultiplication(scaleMatrix)
                              .matrixMultiplication(rotationMatrix); */
            vertices[i] = scaleMatrixM * vertices[i];
            vertices[i] = rotationMatrix * vertices[i];
        }

        Vector<2> renderVectors[8];
        double projectionMatrix[2][3] = {
            {1, 0, 0},
            {0, 1, 0}};
        // lets make a cube in the 3D space creating vertexes with the Vector3 class in front of the plane z = 0

        Matrix<2, 3> projectionMatrixM(projectionMatrix);

        for (int i = 0; i < 8; i++)
        {
            /*  renderVectors[i] = vertices[i].matrixMultiplication(projectionMatrix); */
            renderVectors[i] = projectionMatrixM * vertices[i];
        }

        // lets scale the points to fit the screen size, lets say the screen is 640x480 and the values are between -5 and 5

        int offsetX = SCREEN_WIDTH / 2;
        int offsetY = SCREEN_HEIGHT / 2;
        int scale = SCREEN_SCALE;

        SDL_Point renderVertexes[8];

        for (int i = 0; i < 8; i++)
        {
            renderVertexes[i].x = (int)(renderVectors[i][0] * scale + offsetX);
            renderVertexes[i].y = (int)(renderVectors[i][1] * scale + offsetY);
        }

        SDL_SetRenderDrawColor(ren, EDGE_COLOR);

        for (int i = 0; i < 4; i++)
        {
            SDL_RenderDrawLine(ren, renderVertexes[i].x, renderVertexes[i].y, renderVertexes[(i + 1) % 4].x, renderVertexes[(i + 1) % 4].y);
            SDL_RenderDrawLine(ren, renderVertexes[i + 4].x, renderVertexes[i + 4].y, renderVertexes[((i + 1) % 4) + 4].x, renderVertexes[((i + 1) % 4) + 4].y);
            SDL_RenderDrawLine(ren, renderVertexes[i].x, renderVertexes[i].y, renderVertexes[i + 4].x, renderVertexes[i + 4].y);
        }

        // Render the changes above
        SDL_RenderPresent(ren);
    }

    return 0;
}
