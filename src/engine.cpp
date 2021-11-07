#include <engine.hpp>

SDL_Window *window;
SDL_Renderer *renderer;

int screenWidth, screenHeight;
int mouseX, mouseY;
bool engine::runningState = true;
vector2 selectedPiece {-1, 0}, lastSelected;
std::vector<vector2> possibleMoves;

SDL_Texture *pieceSurfaces[6];

void drawGrid(int cellXCount, int cellYCount, int cellWidth, int cellHeight){
    for (int i = 0; i <= cellXCount; ++i){
        for (int j = 0; j <= cellYCount; ++j){
            if ((i + j) % 2 == 0){
                SDL_Rect rect{i * cellWidth, j * cellHeight, cellWidth, cellHeight};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void drawPieces(piece pieces[BOARD_HEIGHT][BOARD_WIDTH]){
    for (int i = 0; i < BOARD_HEIGHT; ++i){
        for (int j = 0; j < BOARD_WIDTH; ++j){
            if (pieces[i][j].type != EMPTY){
                SDL_Rect rect{i * 100, j * 100, 100, 100};
                if (pieces[i][j].team == 2){
                    SDL_SetTextureColorMod(pieceSurfaces[pieces[i][j].type], 150, 150, 0);
                }
                SDL_RenderCopy(renderer, pieceSurfaces[pieces[i][j].type], NULL, &rect);
                SDL_SetTextureColorMod(pieceSurfaces[pieces[i][j].type], 255, 255, 255);
            }
        }
    }
}

void drawPotentialMoves(){
    for (vector2 move : possibleMoves){
        SDL_Rect rect{move.x * 100 + 33, move.y * 100 + 33, 33, 33};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void engine::init(int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG){
        screenWidth = width;
        screenHeight = height;

        window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


        pieceSurfaces[0] = IMG_LoadTexture(renderer, "pieces/pawn.png");
        pieceSurfaces[1] = IMG_LoadTexture(renderer, "pieces/knight.png");
        pieceSurfaces[2] = IMG_LoadTexture(renderer, "pieces/bishop.png");
        pieceSurfaces[3] = IMG_LoadTexture(renderer, "pieces/rook.png");
        pieceSurfaces[4] = IMG_LoadTexture(renderer, "pieces/queen.png");
        pieceSurfaces[5] = IMG_LoadTexture(renderer, "pieces/king.png");

        if (renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else {
            SDL_Log("Failed to initialize. Error: %s", SDL_GetError());
            std::exit(1);
        }
    } else {
        SDL_Log("Failed to initialize. Errors:\n %s", SDL_GetError());
        std::exit(1);
    }
}

void engine::update(){
    SDL_GetMouseState(&mouseX, &mouseY);
    // Event handling. 
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_KEYDOWN:{
            switch (event.key.keysym.sym){
                case SDLK_ESCAPE: {
                    engine::runningState = false;
                    break;
                }
            }
        }
        case SDL_MOUSEBUTTONDOWN:{
            if (event.button.button == SDL_BUTTON_LEFT){
                selectedPiece = {(int)mouseX / 100, (int)mouseY / 100};
                if (possibleMoves.empty()){
                    lastSelected = selectedPiece;
                    possibleMoves = game::getPossibleMoves(game::grid[selectedPiece.x][selectedPiece.y], selectedPiece);
                } else {
                    bool moveValid = false;
                    for (vector2 move : possibleMoves){
                        if (move.x == selectedPiece.x && move.y == selectedPiece.y){
                            moveValid = true;
                            break;
                        }
                    }

                    if (moveValid){
                        game::movePieces(game::grid, lastSelected, selectedPiece);
                        lastSelected = {-1, -1};
                        possibleMoves.clear();
                    } else {
                        possibleMoves.clear();
                        possibleMoves = game::getPossibleMoves(game::grid[selectedPiece.x][selectedPiece.y], selectedPiece);
                        lastSelected = selectedPiece;
                    }
                }
            }
            break;
        }
    }
}

void engine::render(){
    SDL_SetRenderDrawColor(renderer, 252, 222, 181, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 173, 113, 57, 255);
    drawGrid(8, 8, 100, 100);
    if (selectedPiece.x != -1){
        SDL_SetRenderDrawColor(renderer, 40, 20, 5, 255);
        SDL_Rect rect{selectedPiece.x * 100, selectedPiece.y * 100, 100, 100};
        SDL_RenderFillRect(renderer, &rect);
    }
    drawPieces(game::grid);
    drawPotentialMoves();
    
    SDL_RenderPresent(renderer);
}

void engine::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
