#include <stdio.h>
#include "../include/GameOverState.h"
#include "../include/Texture.h"

GameOverState::GameOverState(){
    currentStateEnum = GAME_OVER_STATE;
    nextStateEnum = GAME_OVER_STATE;
    userQuit = false;

}

GameOverState::~GameOverState(){

}

void GameOverState::stateEnter(){
    printf("GAME OVER");
}

void GameOverState::stateEvent(){
    SDL_Event event;
    // Event loop //
    while(SDL_PollEvent(&event)!=0){

        // Quits game //
        if(event.type==SDL_QUIT)
        {
            userQuit=true;
        }
    }
}

StateEnum GameOverState::stateUpdate(){
    if (currentStateEnum != nextStateEnum) {
        return nextStateEnum;
    }
    return currentStateEnum;
}

void GameOverState::stateRender(){
    // Light wood color //
    SDL_SetRenderDrawColor(gRenderer, 0xD4, 0x9A, 0x6A, 0xFF);
    // Refreshs screen //
    SDL_RenderClear(gRenderer);
}

bool GameOverState::stateExit(){
    return userQuit;
}

bool GameOverState::loadMedia(){
    return false;
}
