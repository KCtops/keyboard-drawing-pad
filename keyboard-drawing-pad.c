#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GRID_SIZE 100
#define CELL_SIZE (WINDOW_WIDTH / GRID_SIZE)
#define MOVE_STEP CELL_SIZE
#define DEFAULT_BRUSH_SIZE CELL_SIZE

int main(int argc, char *argv[]) {
    // Print instructions
    printf("Welcome to the Grid-Based Drawing Pad!\n");
    printf("Controls:\n");
    printf("  W/A/S/D: Move cursor up/left/down/right (snap to grid)\n");
    printf("  SPACE: Start drawing\n");
    printf("  R/F: Increase/Decrease brush size (1 to 10 grid cells)\n");
    printf("  1-8: Change brush color\n");
    printf("  X: Clear the canvas\n");
    printf("  ESC: Quit\n\n");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Grid Drawing Pad", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Function to draw the grid
    void drawGrid() {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Light gray
        for (int i = 0; i <= GRID_SIZE; i++) {
            SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_HEIGHT); // Vertical
            SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, WINDOW_WIDTH, i * CELL_SIZE); // Horizontal
        }
    }

    // Canvas to track drawn pixels
    SDL_Texture *canvas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderTarget(renderer, canvas);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Clear to white
    SDL_RenderClear(renderer);
    drawGrid();
    SDL_SetRenderTarget(renderer, NULL);

    int x = 0, y = 0;
    int drawing = 0;
    int brushSize = DEFAULT_BRUSH_SIZE;
    SDL_Color brushColor = {0, 0, 0, 255};

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: y -= brushSize; break;  // Move up by brush size
                    case SDLK_s: y += brushSize; break;  // Move down by brush size
                    case SDLK_a: x -= brushSize; break;  // Move left by brush size
                    case SDLK_d: x += brushSize; break;  // Move right by brush size
                    case SDLK_q:  // Move up-left
                        x -= brushSize;
                        y -= brushSize;
                        break;
                    case SDLK_e:  // Move up-right
                        x += brushSize;
                        y -= brushSize;
                        break;
                    case SDLK_z:  // Move down-left
                        x -= brushSize;
                        y += brushSize;
                        break;
                    case SDLK_c:  // Move down-right
                        x += brushSize;
                        y += brushSize;
                        break;
                    case SDLK_SPACE: drawing = 1; break;
                    case SDLK_r:
                        brushSize += CELL_SIZE;
                        if (brushSize > CELL_SIZE * 10) brushSize = CELL_SIZE * 10;
                        break;
                    case SDLK_f:
                        brushSize -= CELL_SIZE;
                        if (brushSize < CELL_SIZE) brushSize = CELL_SIZE;
                        break;
                    case SDLK_1: brushColor = (SDL_Color){0, 0, 0, 255}; break;
                    case SDLK_2: brushColor = (SDL_Color){0, 0, 255, 255}; break;
                    case SDLK_3: brushColor = (SDL_Color){0, 255, 0, 255}; break;
                    case SDLK_4: brushColor = (SDL_Color){0, 255, 255, 255}; break;
                    case SDLK_5: brushColor = (SDL_Color){255, 0, 0, 255}; break;
                    case SDLK_6: brushColor = (SDL_Color){255, 0, 255, 255}; break;
                    case SDLK_7: brushColor = (SDL_Color){255, 255, 0, 255}; break;
                    case SDLK_8: brushColor = (SDL_Color){255, 255, 255, 255}; break;
                    case SDLK_x:
                        SDL_SetRenderTarget(renderer, canvas);
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Clear to white
                        SDL_RenderClear(renderer);
                        drawGrid();
                        SDL_SetRenderTarget(renderer, NULL);
                        break;
                    case SDLK_ESCAPE: running = 0; break;
                }
            }

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) {
                drawing = 0;
            }
        }

        // Ensure the cursor aligns with the grid
        if (x < 0) x = 0;
        if (x >= WINDOW_WIDTH) x = WINDOW_WIDTH - CELL_SIZE;
        if (y < 0) y = 0;
        if (y >= WINDOW_HEIGHT) y = WINDOW_HEIGHT - CELL_SIZE;

        // Snap to grid after movement
        x = (x / brushSize) * brushSize;
        y = (y / brushSize) * brushSize;

        // Draw on the canvas when active
        if (drawing) {
            SDL_SetRenderTarget(renderer, canvas);
            SDL_SetRenderDrawColor(renderer, brushColor.r, brushColor.g, brushColor.b, brushColor.a);
            SDL_Rect rect = {x, y, brushSize, brushSize};
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderTarget(renderer, NULL);
        }

        // Render the canvas
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, canvas, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyTexture(canvas);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
