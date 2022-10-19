#include "../include/CheckersBoard.h"
#include "../include/GameState.h"
#include "../include/Texture.h"

//Método que ubica las fichas en el tablero
CheckersBoard::CheckersBoard(){
    for (int y = 0; y < 8; y++)
    {
        vector<int> rowVector;
        for (int x = 0; x < 8; x++)
        {
            rowVector.push_back(0);
        }
        virtualBoard.push_back(rowVector);
    }
    highLight = false;
    highLightSelected.x = NULL;
    highLightSelected.y = NULL;
}

//Constructor de la clase
CheckersBoard::~CheckersBoard(){
    virtualBoard.clear();
}

ostream & operator << (ostream & output, CheckersBoard & boardPassed) {
    output << "========" << endl;
    for (int y=0; y<8; y++) {
        for (int x=0; x<8; x++) {
            if ((y + x) % 2 == 1) {
                output << boardPassed.virtualBoard[x][y];
            }
            else {
                output << " ";
            }
        }
        output << endl;
    }
    return output;
}

//Método que posiciona las fichas en el tablero
void CheckersBoard::turnHighLightOn(int x,int y){
    highLight = true;
    highLightSelected.x = x * 80;
    highLightSelected.y = y * 80;
}

//Método que verifica si la posición está disponible para ubicar una ficha
void CheckersBoard::turnHighLightOff(){
    highLight = false;
    validLocations.clear();
}

//Método que dibuja el tablero
void CheckersBoard::drawBoard(){
    
    bool indent = false;
    int xStart;
    // Dark wood colour //
    SDL_SetRenderDrawColor( gRenderer, 0x55, 0x27, 0x00, 0xFF );
    
    for(int y=0;y<SCREEN_HEIGHT;y+=BUTTON_HEIGHT){
        if (indent) {
            xStart = BUTTON_WIDTH;
            indent = false;
        }
        else{
            xStart = 0;
            indent = true;
        }
        for(int x=xStart;x<SCREEN_WIDTH;x+=2*BUTTON_WIDTH){
            SDL_Rect redRect = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
            SDL_RenderFillRect( gRenderer, &redRect);
        }
    }
    drawHighlights();
    
}

//Método que dibuja las líneas en el tablero
void CheckersBoard::drawHighlights() {
    if (highLight) {
        // Set to white //
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        // Create the outline rect //
        SDL_Rect outLine = {highLightSelected.x, highLightSelected.y, BUTTON_WIDTH, BUTTON_HEIGHT};
        // Call to render //
        SDL_RenderDrawRect(gRenderer, &outLine);
        
        // Set to white //
        SDL_SetRenderDrawColor( gRenderer, 0x55, 0xFF, 0x55, 0xFF );
        
        for (int indexOfValidMoves = 0; indexOfValidMoves < validLocations.size(); indexOfValidMoves++) {
            SDL_Rect outLineValid = {validLocations[indexOfValidMoves].x * 80, validLocations[indexOfValidMoves].y * 80, BUTTON_WIDTH, BUTTON_HEIGHT};
            // Call to render //
            SDL_RenderDrawRect(gRenderer, &outLineValid);
        }
    }
}

//Método que dibuja las piecas del tablero
void CheckersBoard::drawBoardPeices(int x, int y, Button *boardButton){
    switch (virtualBoard[x][y]) {
            
        case RED_PIECE:
            currentSprite = RED_PIECE;
            boardButton->render(currentSprite-1);
            break;
            
        case BLACK_PIECE:
            currentSprite = BLACK_PIECE;
            boardButton->render(currentSprite-1);
            break;
            
        case RED_KING:
            currentSprite = RED_KING;
            boardButton->render(currentSprite-1);
            break;
            
        case BLACK_KING:
            currentSprite = BLACK_KING;
            boardButton->render(currentSprite-1);
            break;

        default:
            break;
    }

}
   