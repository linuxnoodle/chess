#include <game.hpp>

// Really should have gone with traditional classes and objects for this...
// Meh, refactor into DOD later.
// Somehow.

char game::currentTurn = 1;

// hardcoded start values, might work on saving positions later
piece game::grid[BOARD_HEIGHT][BOARD_WIDTH]{
    {{ROOK, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {ROOK, 1}},
    {{KNIGHT, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {KNIGHT, 1}},
    {{BISHOP, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {BISHOP, 1}},
    {{KING, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {KING, 1}},
    {{QUEEN, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {QUEEN, 1}},
    {{BISHOP, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {BISHOP, 1}},
    {{KNIGHT, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {KNIGHT, 1}},
    {{ROOK, 2}, {PAWN, 2}, {EMPTY}, {EMPTY}, {EMPTY}, {EMPTY}, {PAWN, 1}, {ROOK, 1}}
};

void game::movePieces(piece (&board)[BOARD_HEIGHT][BOARD_WIDTH], vector2 firstPiece, vector2 secondPiece){
    board[secondPiece.x][secondPiece.y] = board[firstPiece.x][firstPiece.y];
    ++board[secondPiece.x][secondPiece.y].moves;
    board[firstPiece.x][firstPiece.y] = {EMPTY};
    game::currentTurn = !(game::currentTurn - 1) + 1;
}

std::vector<vector2> game::getPossibleMoves(piece p, vector2 currentPosition){
    std::vector<vector2> moves;
    if (p.team != game::currentTurn){
        return moves;    
    }
    // Destination already full
    //if (grid[selectedDestination.x][selectedDestination.y] != EMPTY)
    switch (p.type){
        case PAWN:{
            // Below should be compiler optimized away, and drastically improves readability
            piece p = grid[currentPosition.x][currentPosition.y];
            if (p.team == 1){
                
                // Front
                if (currentPosition.y > 0 && grid[currentPosition.x][currentPosition.y - 1].type == EMPTY){
                    moves.push_back({currentPosition.x, currentPosition.y - 1});
                }
                
                // Double on first
                if (currentPosition.y > 1 && p.moves == 0 && grid[currentPosition.x][currentPosition.y - 1].type == EMPTY && grid[currentPosition.x][currentPosition.y - 2].type == EMPTY){
                    moves.push_back({currentPosition.x, currentPosition.y - 2});
                }
                
                // Top-left
                if (currentPosition.x > 0 && currentPosition.y > 0){
                    piece topleft = grid[currentPosition.x - 1][currentPosition.y - 1]; 
                    // If piece in top left is on another team
                    if (topleft.type != EMPTY && topleft.team != p.team){
                        moves.push_back({currentPosition.x - 1, currentPosition.y - 1});
                    }
                }
                
                // Top-right
                if (currentPosition.x < 7 && currentPosition.y > 0){
                    piece topright = grid[currentPosition.x + 1][currentPosition.y - 1];
                    // If piece in top right is on another team
                    if (topright.type != EMPTY && topright.team != p.team){
                        moves.push_back({currentPosition.x + 1, currentPosition.y - 1});
                    }
                }
            } else if (p.team == 2){
                
                // Front
                if (currentPosition.y < 7 && grid[currentPosition.x][currentPosition.y + 1].type == EMPTY){
                    moves.push_back({currentPosition.x, currentPosition.y + 1});
                }
                
                // Double on first
                if (currentPosition.y < 6 && p.moves == 0 && grid[currentPosition.x][currentPosition.y + 1].type == EMPTY && grid[currentPosition.x][currentPosition.y + 2].type == EMPTY){
                    moves.push_back({currentPosition.x, currentPosition.y + 2});
                }
                
                // Bottom-left
                if (currentPosition.x > 0 && currentPosition.y < 7){
                    piece bottomleft = grid[currentPosition.x - 1][currentPosition.y + 1]; 
                    // If piece in top left is on another team
                    if (bottomleft.type != EMPTY && bottomleft.team != p.team){
                        moves.push_back({currentPosition.x - 1, currentPosition.y + 1});
                    }
                }

                if (currentPosition.x < 7 && currentPosition.y > 0){
                    piece bottomright = grid[currentPosition.x + 1][currentPosition.y + 1];
                    // If piece in top right is on another team
                    if (bottomright.type != EMPTY && bottomright.team != p.team){
                        moves.push_back({currentPosition.x + 1, currentPosition.y + 1});
                    }
                }
            }
            break;
        }
        case KNIGHT:{
            break;
        }
        case BISHOP:{
            break;
        }
        case ROOK:{
            break;
        }
        case QUEEN:{
            break;
        }
        case KING:{
            break;
        }
        default:
            break;
    } 
    return moves;
}

bool checkIfColliding(vector2 input, vector2 box, vector2 boxSize){
    return (input.x > box.x && input.x < (box.x + boxSize.x)) && (input.y > box.y && input.y < (box.y + boxSize.y));
}
